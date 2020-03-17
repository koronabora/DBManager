#include "DBHandler.h"
#include "SQL.h"
#include <QThread>

void DBHandler::init()
{
	db = QSqlDatabase::addDatabase(DB_PLUGIN);

	db.setHostName(DB_HOST);
	db.setDatabaseName(DB_BASE);
	db.setUserName(DB_USER);
	db.setPassword(DB_PASS);
	db.setPort(DB_PORT);

	bool ok = db.open();
	emit haveAnError("Database status: " + QString::number(ok));
	if (!ok)
		emit haveAnError(db.lastError().text());
}

DBHandler::DBHandler()
{
}

void DBHandler::run()
{
	init();
}

DBHandler::~DBHandler()
{
	db.close();
	emit workFinished();
}

////////////////////////////////////////////////////////////////
//				TAG
////////////////////////////////////////////////////////////////

void DBHandler::createTag(const dbTag& data)
{
	QSqlQuery query;
	query.prepare(CREATE_TAG);
	query.bindValue(0, data.ID);
	query.bindValue(1, data.CreatedAt);
	query.bindValue(2, data.UpdatedAt);
	query.bindValue(3, QVariant(QVariant::DateTime));
	query.bindValue(4, data.Name);
	query.exec();
	QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit tagCreated(data.ID, false);
	}
	else
		emit tagCreated(data.ID, true);
}

dbTag DBHandler::parseTag(const QSqlQuery& q, bool& res)
{
	dbTag t;
	const QString ID = q.value(0).toString();
	bool ok;
	const long long id = ID.toLongLong(&ok);
	if (!ok)
	{
		emit haveAnError("Could not convert " + ID + " to long!");
		res = false;
	}
	const QDateTime created = q.value(1).toDateTime();
	const QDateTime updated = q.value(2).toDateTime();
	const QDateTime deleted = q.value(3).toDateTime();
	//emit haveAnError("Created: " + created.toString() + "; updated: " + updated.toString() + "; deleted: " + deleted.toString());
	const QString name = q.value(4).toString();
	//const QString test = q.value(6).toString();

	t.ID = id;
	t.CreatedAt = created;
	t.UpdatedAt = updated;
	t.DeletedAt = deleted;
	t.Name = name;
	return t;
}

void DBHandler::readTag()
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_TAG);
	query.exec();
	QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	else
	{
		QVector<bool> results;
		while (query.next())
		{
			bool foo;
			emit hasTag(parseTag(query, foo));
			results.push_back(foo);
		}
		isOk = results.contains(false);
	}
	isOk ? emit tagReaded(0, true) : emit tagReaded(0, false);
}

void DBHandler::readTag(const long long& id)
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_TAG_BY_ID);
	query.bindValue(0, id);
	query.exec();
	QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	if (query.next())
	{
		isOk = true;
		emit hasTag(parseTag(query, isOk));
	}
	isOk ? emit tagReaded(id, true) : emit tagReaded(id, false);
}

void DBHandler::updateTag(const dbTag& data)
{
	QSqlQuery query;
	query.prepare(UPDATE_TAG);
	query.bindValue(0, data.UpdatedAt);
	query.bindValue(1, data.Name);
	query.bindValue(2, data.ID);
	query.exec();
	QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit tagUpdated(data.ID, false);
	}
	else
		emit tagUpdated(data.ID, true);
}

void DBHandler::deleteTag(const dbTag& data)
{
	QSqlQuery query;
	query.prepare(DELETE_TAG);
	query.bindValue(0, data.DeletedAt);
	query.bindValue(1, data.ID);
	query.exec();
	QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit tagDeleted(data.ID, false);
	}
	else
		emit tagDeleted(data.ID, true);
}

////////////////////////////////////////////////////////////////
//				USER
////////////////////////////////////////////////////////////////

void DBHandler::createUser(const dbUser& data)
{
	QSqlQuery query;
	query.prepare(CREATE_USER);
	query.bindValue(0, data.ID);
	query.bindValue(1, data.CreatedAt);
	query.bindValue(2, data.UpdatedAt);
	query.bindValue(3, QVariant(QVariant::DateTime));
	query.bindValue(4, data.Name);
	query.bindValue(5, data.Surname);
	query.bindValue(6, serializeStringList(data.Contacts));
	query.bindValue(7, data.PassHash);
	query.bindValue(8, data.Login);
	query.bindValue(9, data.Userpic);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit userCreated(data.ID, false);
	}
	else
		emit userCreated(data.ID, true);
}

dbUser DBHandler::parseUser(const QSqlQuery& q, bool& res)
{
	dbUser u;
	const QString ID = q.value(0).toString();
	bool ok;
	const long long id = ID.toLongLong(&ok);
	if (!ok)
	{
		res = false;
		emit haveAnError("Could not convert " + ID + " to long!");
	}
	QString foo = q.value(1).toString();
	const QDateTime created_at = QDateTime::fromString(q.value(1).toString());
	const QDateTime updated_at = QDateTime::fromString(q.value(2).toString());
	const QDateTime deleted_at = QDateTime::fromString(q.value(3).toString());
	const QString name = q.value(4).toString();
	const QString surname = q.value(5).toString();
	QString contacts = q.value(6).toString();
	contacts.replace('{', "");
	contacts.replace('}', "");
	const QStringList contactsList = contacts.split(',');
	const QString pass_hash = q.value(7).toString();
	const QString login = q.value(8).toString();
	const QString userpic = q.value(9).toString();

	u.ID = id;
	u.Name = name;
	u.Surname = surname;
	u.Contacts = contactsList;
	u.CreatedAt = created_at;
	u.DeletedAt = deleted_at;
	u.UpdatedAt = updated_at;
	u.Surname = surname;
	u.Login = login;
	u.PassHash = pass_hash;
	u.Userpic = userpic;

	return u;
}

void DBHandler::readUser()
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_USER);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	else
	{
		QVector<bool> results;
		while (query.next())
		{
			bool foo;
			emit hasUser(parseUser(query, foo));
			results.push_back(foo);
		}
		isOk = results.contains(false);
	}
	isOk ? emit userReaded(0, true) : emit userReaded(0, false);
}

void DBHandler::readUser(const long long& id)
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_USER);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	else if (query.next())
	{
		isOk = true;
		emit hasUser(parseUser(query, isOk));
	}
	isOk ? emit userReaded(id, true) : emit userReaded(id, false);
}

void DBHandler::updateUser(const dbUser& data)
{
	QSqlQuery query;
	query.prepare(UPDATE_USER);
	query.bindValue(0, data.UpdatedAt);
	query.bindValue(1, data.Name);
	query.bindValue(2, data.Surname);
	query.bindValue(3, serializeStringList(data.Contacts));
	query.bindValue(4, data.PassHash);
	query.bindValue(5, data.Login);
	query.bindValue(6, data.Userpic);
	query.bindValue(7, data.ID);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit userUpdated(data.ID, false);
	}
	else
		emit userUpdated(data.ID, true);
}

void DBHandler::deleteUser(const dbUser& data)
{
	QSqlQuery query;
	query.prepare(CREATE_USER);
	query.bindValue(0, data.DeletedAt);
	query.bindValue(1, data.ID);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit userDeleted(data.ID, false);
	}
	else
		emit userDeleted(data.ID, true);
}

////////////////////////////////////////////////////////////////
//				EVENT
////////////////////////////////////////////////////////////////

void DBHandler::createEvent(const dbEvent& data)
{
	QSqlQuery query;
	query.prepare(CREATE_EVENT);
	query.bindValue(0, data.ID);
	query.bindValue(1, data.Name);
	query.bindValue(2, data.CreatedAt);
	query.bindValue(3, data.UpdatedAt);
	query.bindValue(4, QVariant(QVariant::DateTime));
	query.bindValue(5, data.ShDescr);
	query.bindValue(6, data.FullDescr);
	query.bindValue(7, data.Routing);
	query.bindValue(8, serializeVector(data.Places));
	query.bindValue(9, serializeVector(data.Users));
	query.bindValue(10, serializeVector(data.Tags));
	query.bindValue(11, data.Rate);
	query.bindValue(12, serializeVector(data.Reviews));
	query.bindValue(13, serializeVector(data.PartnerSite));
	query.bindValue(14, serializeVector(data.Media));
	query.bindValue(15, serializeStringList(data.Timetable));
	query.bindValue(16, data.Extra1);
	query.bindValue(17, data.Extra2);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit eventCreated(data.ID, false);
	}
	else
		emit eventCreated(data.ID, true);
}

dbEvent DBHandler::parseEvent(const QSqlQuery& q, bool& res)
{
	const QString ID = q.value(0).toString();
	bool ok;
	const long long id = ID.toLongLong(&ok);
	if (!ok)
	{
		emit haveAnError("Could not convert " + ID + " to long!");
		res = false;
	}
	const QString name = q.value(1).toString();
	const QDateTime created_at = QDateTime::fromString(q.value(2).toString());
	const QDateTime updated_at = QDateTime::fromString(q.value(3).toString());
	const QDateTime deleted_at = QDateTime::fromString(q.value(4).toString());

	const QString sh_descr = q.value(5).toString();
	const QString full_descr = q.value(6).toString();
	const QString routing = q.value(7).toString();
	const QVector<long long> places = deserializeVector(q.value(8).toString());
	const QVector<long long> users = deserializeVector(q.value(9).toString());
	const QVector<long long> tags = deserializeVector(q.value(10).toString());
	const long long rates = q.value(11).toLongLong();
	const QVector<long long> reviews = deserializeVector(q.value(12).toString());
	const QVector<long long> partner_sites = deserializeVector(q.value(13).toString());
	const QVector<long long> media = deserializeVector(q.value(14).toString());
	const QStringList timetable = deserializeStringList(q.value(15).toString());
	const QString extra1 = q.value(16).toString();
	const QString extra2 = q.value(17).toString();

	dbEvent e;
	e.ID = id;
	e.CreatedAt = created_at;
	e.UpdatedAt = updated_at;
	e.DeletedAt = deleted_at;
	e.ShDescr = sh_descr;
	e.FullDescr = full_descr;
	e.Routing = routing;
	e.Places = places;
	e.Users = users;
	e.Tags = tags;
	e.Rate = rates;
	e.Reviews = reviews;
	e.PartnerSite = partner_sites;
	e.Media = media;
	e.Timetable = timetable;
	e.Extra1 = extra1;
	e.Extra2 = extra2;
	return e;
}

void DBHandler::readEvent()
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_EVENT);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	else
	{
		QVector<bool> results;
		while (query.next())
		{
			bool foo;
			emit hasEvent(parseEvent(query, foo));
			results.push_back(foo);
		}
		isOk = results.contains(false);
	}
	isOk ? emit eventReaded(0, true) : emit eventReaded(0, false);
}

void DBHandler::readEvent(const long long& id)
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_EVENT);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	else if (query.next())
	{
		isOk = true;
		emit hasEvent(parseEvent(query, isOk));
	}
	isOk ? emit eventReaded(id, true) : emit eventReaded(id, false);
}

void DBHandler::updateEvent(const dbEvent& data)
{
	QSqlQuery query;
	query.prepare(UPDATE_EVENT);
	query.bindValue(0, data.Name);
	query.bindValue(1, data.UpdatedAt);
	query.bindValue(2, data.ShDescr);
	query.bindValue(3, data.FullDescr);
	query.bindValue(4, data.Routing);
	query.bindValue(5, serializeVector(data.Places));
	query.bindValue(6, serializeVector(data.Users));
	query.bindValue(7, serializeVector(data.Tags));
	query.bindValue(8, data.Rate);
	query.bindValue(9, serializeVector(data.Reviews));
	query.bindValue(10, serializeVector(data.PartnerSite));
	query.bindValue(11, serializeVector(data.Media));
	query.bindValue(12, serializeStringList(data.Timetable));
	query.bindValue(13, data.Extra1);
	query.bindValue(14, data.Extra2);
	query.bindValue(15, data.ID);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit eventUpdated(data.ID, false);
	}
	else
		emit eventUpdated(data.ID, true);
}

void DBHandler::deleteEvent(const dbEvent& data)
{
	QSqlQuery query;
	query.prepare(DELETE_EVENT);
	query.bindValue(0, data.DeletedAt);
	query.bindValue(1, data.ID);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit eventDeleted(data.ID, false);
	}
	else
		emit eventDeleted(data.ID, true);
}

////////////////////////////////////////////////////////////////
//				PARTNER SITE
////////////////////////////////////////////////////////////////

void DBHandler::createPSite(const dbPartnerSite& data)
{
	QSqlQuery query;
	query.prepare(CREATE_PSITE);
	query.bindValue(0, data.ID);
	query.bindValue(1, data.CreatedAt);
	query.bindValue(2, data.UpdatedAt);
	query.bindValue(3, QVariant(QVariant::DateTime));
	query.bindValue(4, data.Ref);
	query.bindValue(5, data.Def);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit pSiteCreated(data.ID, false);
	}
	else
		emit pSiteCreated(data.ID, true);
}

dbPartnerSite DBHandler::parsePartnerSite(const QSqlQuery& q, bool& res)
{
	const QString ID = q.value(0).toString();
	bool ok;
	const long long id = ID.toLongLong(&ok);
	if (!ok)
	{
		emit haveAnError("Could not convert " + ID + " to long!");
		res = false;
	}
	const QDateTime created_at = QDateTime::fromString(q.value(1).toString());
	const QDateTime updated_at = QDateTime::fromString(q.value(2).toString());
	const QDateTime deleted_at = QDateTime::fromString(q.value(3).toString());

	const QString ref = q.value(4).toString();
	const QString def = q.value(5).toString();
	dbPartnerSite ps;
	ps.ID = id;
	ps.CreatedAt = created_at;
	ps.UpdatedAt = updated_at;
	ps.DeletedAt = deleted_at;
	ps.Ref = ref;
	ps.Def = def;
	return ps;
}

void DBHandler::readPSite()
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_PSITE);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	else
	{
		QVector<bool> results;
		while (query.next())
		{
			bool foo;
			emit hasPSite(parsePartnerSite(query, foo));
			results.push_back(foo);
		}
		isOk = results.contains(false);
	}
	isOk ? emit pSiteReaded(0, true) : emit pSiteReaded(0, false);
}

void DBHandler::readPSite(const long long& id)
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_PSITE);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	else if (query.next())
	{
		isOk = true;
		emit hasPSite(parsePartnerSite(query, isOk));
	}
	isOk ? emit pSiteReaded(id, true) : emit pSiteReaded(id, false);
}

void DBHandler::updatePSite(const dbPartnerSite& data)
{
	QSqlQuery query;
	query.prepare(UPDATE_PSITE);
	query.bindValue(0, data.UpdatedAt);
	query.bindValue(1, data.Ref);
	query.bindValue(2, data.Def);
	query.bindValue(3, data.ID);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit pSiteUpdated(data.ID, false);
	}
	else
		emit pSiteUpdated(data.ID, true);
}

void DBHandler::deletePSite(const dbPartnerSite& data)
{
	QSqlQuery query;
	query.prepare(DELETE_PSITE);
	query.bindValue(0, data.DeletedAt);
	query.bindValue(1, data.ID);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit pSiteDeleted(data.ID, false);
	}
	else
		emit pSiteDeleted(data.ID, true);
}

////////////////////////////////////////////////////////////////
//				REVIEW
////////////////////////////////////////////////////////////////

void DBHandler::createReview(const dbReview& data)
{
	QSqlQuery query;
	query.prepare(CREATE_REVIEW);
	query.bindValue(0, data.ID);
	query.bindValue(1, data.CreatedAt);
	query.bindValue(2, data.UpdatedAt);
	query.bindValue(3, QVariant(QVariant::DateTime));
	query.bindValue(4, data.Text);
	query.bindValue(5, data.Rate);
	query.bindValue(6, serializeVector(data.Users));
	query.bindValue(7, data.AddTime);
	query.exec();
	QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit reviewCreated(data.ID, false);
	}
	else
		emit reviewCreated(data.ID, true);
}

dbReview DBHandler::parseReview(const QSqlQuery& q, bool& res)
{
	const QString ID = q.value(0).toString();
	bool ok;
	const long long id = ID.toLongLong(&ok);
	if (!ok)
	{
		emit haveAnError("Could not convert " + ID + " to long!");
		res = false;
	}
	const QDateTime created_at = QDateTime::fromString(q.value(1).toString());
	const QDateTime updated_at = QDateTime::fromString(q.value(2).toString());
	const QDateTime deleted_at = QDateTime::fromString(q.value(3).toString());

	const QString text = q.value(4).toString();
	long rates = q.value(5).toLongLong();
	const QVector<long long> users = deserializeVector(q.value(6).toString());
	const QDateTime add_time = QDateTime::fromString(q.value(7).toString());

	dbReview e;
	e.ID = id;
	e.CreatedAt = created_at;
	e.UpdatedAt = updated_at;
	e.DeletedAt = deleted_at;
	e.Text = text;
	e.Rate = rates;
	e.Users = users;
	e.AddTime = add_time;
	return e;
}

void DBHandler::readReview()
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_REVIEW);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	else
	{
		QVector<bool> results;
		while (query.next())
		{
			bool foo;
			emit hasReview(parseReview(query, foo));
			results.push_back(foo);
		}
		isOk = results.contains(false);
	}
	isOk ? emit reviewReaded(0, true) : emit reviewReaded(0, false);
}

void DBHandler::readReview(const long long& id)
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_REVIEW);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	else if (query.next())
	{
		isOk = true;
		emit hasReview(parseReview(query, isOk));
	}
	isOk ? emit reviewReaded(id, true) : emit reviewReaded(id, false);
}

void DBHandler::updateReview(const dbReview& data)
{
	QSqlQuery query;
	query.prepare(UPDATE_REVIEW);
	query.bindValue(0, data.UpdatedAt);
	query.bindValue(1, data.Text);
	query.bindValue(2, data.Rate);
	query.bindValue(3, serializeVector(data.Users));
	query.bindValue(4, data.AddTime);
	query.bindValue(5, data.ID);
	query.exec();
	QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit reviewUpdated(data.ID, false);
	}
	else
		emit reviewUpdated(data.ID, true);
}

void DBHandler::deleteReview(const dbReview& data)
{
	QSqlQuery query;
	query.prepare(DELETE_REVIEW);
	query.bindValue(0, data.DeletedAt);
	query.bindValue(1, data.ID);
	query.exec();
	QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit reviewDeleted(data.ID, false);
	}
	else
		emit reviewDeleted(data.ID, true);
}

////////////////////////////////////////////////////////////////
//				MEDIA
////////////////////////////////////////////////////////////////

void DBHandler::createMedia(const dbMedia& data)
{
	QSqlQuery query;
	query.prepare(CREATE_MEDIA);
	query.bindValue(0, data.ID);
	query.bindValue(1, data.CreatedAt);
	query.bindValue(2, data.UpdatedAt);
	query.bindValue(3, QVariant(QVariant::DateTime));
	query.bindValue(4, data.Name);
	query.bindValue(5, data.Rate);
	query.bindValue(6, serializeStringList(data.References));
	query.bindValue(7, data.Descr);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit mediaCreated(data.ID, false);
	}
	else
		emit mediaCreated(data.ID, true);
}

dbMedia DBHandler::parseMedia(const QSqlQuery& q, bool& res)
{
	const QString ID = q.value(0).toString();
	bool ok;
	const long long id = ID.toLongLong(&ok);
	if (!ok)
	{
		emit haveAnError("Could not convert " + ID + " to long!");
		res = false;
	}
	const QDateTime created_at = QDateTime::fromString(q.value(1).toString());
	const QDateTime updated_at = QDateTime::fromString(q.value(2).toString());
	const QDateTime deleted_at = QDateTime::fromString(q.value(3).toString());

	const QString name = q.value(4).toString();
	const long rates = q.value(5).toLongLong();
	const QStringList refs = deserializeStringList(q.value(6).toString());
	const QString descr = q.value(7).toString();

	dbMedia e;
	e.ID = id;
	e.CreatedAt = created_at;
	e.UpdatedAt = updated_at;
	e.DeletedAt = deleted_at;
	e.Name = name;
	e.Rate = rates;
	e.References = refs;
	//e.Events = events;
	e.Descr = descr;
	return e;
}

void DBHandler::readMedia()
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_MEDIA);
	query.exec();
	QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	else
	{
		QVector<bool> results;
		while (query.next())
		{
			bool foo;
			emit hasMedia(parseMedia(query, foo));
			results.push_back(foo);
		}
		isOk = results.contains(false);
	}
	isOk ? emit mediaReaded(0, true) : emit mediaReaded(0, false);
}

void DBHandler::readMedia(const long long& id)
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_MEDIA);
	query.exec();
	QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	else if (query.next())
	{
		isOk = true;
		emit hasMedia(parseMedia(query, isOk));
	}
	isOk ? emit mediaReaded(id, true) : emit mediaReaded(id, false);
}

void DBHandler::updateMedia(const dbMedia& data)
{
	QSqlQuery query;
	query.prepare(UPDATE_MEDIA);
	query.bindValue(0, data.UpdatedAt);
	query.bindValue(1, data.Name);
	query.bindValue(2, data.Rate);
	query.bindValue(3, serializeStringList(data.References));
	query.bindValue(4, data.Descr);
	query.bindValue(5, data.ID);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit mediaUpdated(data.ID, false);
	}
	else
		emit mediaUpdated(data.ID, true);
}

void DBHandler::deleteMedia(const dbMedia& data)
{
	QSqlQuery query;
	query.prepare(DELETE_MEDIA);
	query.bindValue(0, data.DeletedAt);
	query.bindValue(1, data.ID);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit mediaDeleted(data.ID, false);
	}
	else
		emit mediaDeleted(data.ID, true);
}

////////////////////////////////////////////////////////////////
//				PLACE
////////////////////////////////////////////////////////////////

void DBHandler::createPlace(const dbPlace& data)
{
	QSqlQuery query;
	query.prepare(CREATE_PLACE);
	query.bindValue(0, data.ID);
	query.bindValue(1, data.CreatedAt);
	query.bindValue(2, data.UpdatedAt);
	query.bindValue(3, QVariant(QVariant::DateTime));
	query.bindValue(4, data.Name);
	query.bindValue(5, data.Descr);
	query.bindValue(6, data.CoordX);
	query.bindValue(7, data.CoordY);
	query.bindValue(8, data.Address);
	query.bindValue(9, serializeVector(data.Media));
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit placeCreated(data.ID, false);
	}
	else
		emit placeCreated(data.ID, true);
}

dbPlace DBHandler::parsePlace(const QSqlQuery& q, bool& res)
{
	const QString ID = q.value(0).toString();
	bool ok;
	const long long id = ID.toLongLong(&ok);
	if (!ok)
	{
		emit haveAnError("Could not convert " + ID + " to long!");
		res = false;
	}
	const QDateTime created_at = QDateTime::fromString(q.value(1).toString());
	const QDateTime updated_at = QDateTime::fromString(q.value(2).toString());
	const QDateTime deleted_at = QDateTime::fromString(q.value(3).toString());

	const QString name = q.value(4).toString();
	const QString descr = q.value(5).toString();
	const qreal coord_x = q.value(6).toDouble();
	const qreal coord_y = q.value(7).toDouble();
	const QString address = q.value(8).toString();
	const QVector<long long> media = deserializeVector(q.value(9).toString());

	dbPlace e;
	e.ID = id;
	e.CreatedAt = created_at;
	e.UpdatedAt = updated_at;
	e.DeletedAt = deleted_at;
	e.Name = name;
	e.Descr = descr;
	e.CoordX = coord_x;
	e.CoordY = coord_y;
	e.Address = address;
	e.Media = media;
	return e;
}

void DBHandler::readPlace()
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_PLACE);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	else
	{
		QVector<bool> results;
		while (query.next())
		{
			bool foo;
			emit hasPlace(parsePlace(query, foo));
			results.push_back(foo);
		}
		isOk = results.contains(false);
	}
	isOk ? emit placeReaded(0, true) : emit placeReaded(0, false);
}

void DBHandler::readPlace(const long long& id)
{
	bool isOk = false;
	QSqlQuery query;
	query.prepare(READ_PLACE);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
		emit haveAnError(err.text());
	else if (query.next())
	{
		isOk = true;
		emit hasPlace(parsePlace(query, isOk));
	}
	isOk ? emit placeReaded(id, true) : emit placeReaded(id, false);
}

void DBHandler::updatePlace(const dbPlace& data)
{
	QSqlQuery query;
	query.prepare(UPDATE_PLACE);
	query.bindValue(0, data.UpdatedAt);
	query.bindValue(1, data.Name);
	query.bindValue(2, data.Descr);
	query.bindValue(3, data.CoordX);
	query.bindValue(4, data.CoordY);
	query.bindValue(5, data.Address);
	query.bindValue(6, serializeVector(data.Media));
	query.bindValue(7, data.ID);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit placeUpdated(data.ID, false);
	}
	else
		emit placeUpdated(data.ID, true);
}

void DBHandler::deletePlace(const dbPlace& data)
{
	QSqlQuery query;
	query.prepare(DELETE_PLACE);
	query.bindValue(0, data.DeletedAt);
	query.bindValue(1, data.ID);
	query.exec();
	const QSqlError err = query.lastError();
	if (err.text().length() > 1)
	{
		emit haveAnError(err.text());
		emit placeDeleted(data.ID, false);
	}
	else
		emit placeDeleted(data.ID, true);
}

////////////////////////////////////////////////////////////////
//				THE END
////////////////////////////////////////////////////////////////

/*void DBHandler::readDB()
{
	readTag();
	readUser();
	readEvent();
	readPSite();
	readReview();
	readMedia();
	readPlace();
	emit allReaded();
}*/

QStringList DBHandler::deserializeStringList(const QString &s)
{
	QString buf = s;
	buf.replace('{', "");
	buf.replace('}', "");
	return buf.split(',');
}

QVector<long long> DBHandler::deserializeVector(const QString &s)
{
	QString buf = s;
	QVector<long long> res;
	buf.replace('{', "");
	buf.replace('}', "");
	QStringList l = buf.split(',');
	for (const QString &s : l)
	{
		res.append(s.toLong());
	}
	return res;
}

QString DBHandler::serializeStringList(const QStringList &ls)
{
	// Skip empty strings
	QStringList v;
	for (QString s : ls)
	{
		s.replace('\r', "");
		s.replace('\t', "");
		s.replace('\n', "");
		if (s.size() > 0)
			v.append(s);
	}
	QString res = "{";
	res.append(v.join(","));
	res.append("}");
	return res;
}

QString DBHandler::serializeVector(const QVector<long long> &v)
{
	QString res = "{";
	for (const long& t : v)
	{
		res.append(QString::number(t));
		res.append(",");
	}
	res.append("}");
	return res;
}

QString DBHandler::serializeDateTime(const QDateTime& dt)
{
	QTimeZone tz = dt.timeZone();
	QString s = QString::number(tz.offsetFromUtc(dt) / 3600);
	if (s.size() == 1)
		s = "+0" + s;
	else
		s = "+" + s;
	const QString res = dt.toString(DATE_TIME_FORMAT) + "000" + s;
	return res;
}

QDateTime DBHandler::deserializeDateTime(const QString& in)
{
	QString foo = in;
	QTimeZone tz(foo.right(3).toUtf8());
	foo.chop(3);
	QDateTime res = QDateTime::fromString(foo, DATE_TIME_FORMAT);
	res.setTimeZone(tz);
	//qDebug() << res.toString();
	return res;
}

