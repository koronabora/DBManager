#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <memory>
#include <QSqlError>
#include <QTimeZone>
#include "Types.h"

using namespace std;

static const QString DATE_TIME_FORMAT = "yyyy-MM-dd hh:mm:ss.zzz";

/*
Мы сигналами запрашиваем у класса выполнить операцию над объектом.
Операция выполняется и обязательно назад прилетает сигнал об успешности операции. Если парсинг прошел неуспшно, в объекте будет мусор, придет сигнал о неуспешности.
*/

// Ha ha! Copypasta HELL!

/*
Возможный вариант решения:
 - сделать класс базы данных у которого есть виртуальные методы
	void bindCreate(QSqlQuery& q);
	void bindReadAll(QSqlQuery& q);
	void bindReadOnce(QSqlQuery& q);
	void bindUpdate(QSqlQuery& q);
	void bindDelete(QSqlQuery& q);
- в этих методах каждый наслденик - логический объект формирует нужные методы
- добавляем метод парсинга
	T parseMyself(QSqlQuery& q);
- ура?
*/

class DBHandler : public QObject
{
	Q_OBJECT

public:
	DBHandler();
	~DBHandler();
	void init();
private:

	QSqlDatabase db;

	QStringList deserializeStringList(const QString &s);
	QVector<long long> deserializeVector(const QString &s);

	QString serializeStringList(const QStringList &ls);
	QString serializeVector(const QVector<long long> &v);

	QString serializeDateTime(const QDateTime& dt);
	QDateTime deserializeDateTime(const QString& in);

	dbTag parseTag(const QSqlQuery& q, bool& res);
	dbUser parseUser(const QSqlQuery& q, bool& res);
	dbEvent parseEvent(const QSqlQuery& q, bool& res);
	dbPartnerSite parsePartnerSite(const QSqlQuery& q, bool& res);
	dbReview parseReview(const QSqlQuery& q, bool& res);
	dbMedia parseMedia(const QSqlQuery& q, bool& res);
	dbPlace parsePlace(const QSqlQuery& q, bool& res);

public slots:

	void createTag(const dbTag& data);
	void readTag();
	void readTag(const long long& id);
	void updateTag(const dbTag& data);
	void deleteTag(const dbTag& data);

	void createUser(const dbUser& data);
	void readUser();
	void readUser(const long long& id);
	void updateUser(const dbUser& data);
	void deleteUser(const dbUser& data);

	void createEvent(const dbEvent& data);
	void readEvent();
	void readEvent(const long long& id);
	void updateEvent(const dbEvent& data);
	void deleteEvent(const dbEvent& data);

	void createPSite(const dbPartnerSite& data);
	void readPSite();
	void readPSite(const long long& id);
	void updatePSite(const dbPartnerSite& data);
	void deletePSite(const dbPartnerSite& data);

	void createReview(const dbReview& data);
	void readReview();
	void readReview(const long long& id);
	void updateReview(const dbReview& data);
	void deleteReview(const dbReview& data);

	void createMedia(const dbMedia& data);
	void readMedia();
	void readMedia(const long long& id);
	void updateMedia(const dbMedia& data);
	void deleteMedia(const dbMedia& data);

	void createPlace(const dbPlace& data);
	void readPlace();
	void readPlace(const long long& id);
	void updatePlace(const dbPlace& data);
	void deletePlace(const dbPlace& data);

	void run();

signals:
	void workFinished();

	void hasEvent(const dbEvent& data);
	void hasPlace(const dbPlace& data);
	void hasMedia(const dbMedia& data);
	void hasUser(const dbUser& data);
	void hasPSite(const dbPartnerSite& data);
	void hasTag(dbTag data);
	void hasReview(const dbReview& data);

	void haveAnError(const QString& s); // logging

	// operation results
	void tagCreated(const long long& id, const bool& res);
	void tagReaded(const long long& id, const bool& res);
	void tagUpdated(const long long& id, const bool& res);
	void tagDeleted(const long long& id, const bool& res);

	void userCreated(const long long& id, const bool& res);
	void userReaded(const long long& id, const bool& res);
	void userUpdated(const long long& id, const bool& res);
	void userDeleted(const long long& id, const bool& res);

	void eventCreated(const long long& id, const bool& res);
	void eventReaded(const long long& id, const bool& res);
	void eventUpdated(const long long& id, const bool& res);
	void eventDeleted(const long long& id, const bool& res);

	void pSiteCreated(const long long& id, const bool& res);
	void pSiteReaded(const long long& id, const bool& res);
	void pSiteUpdated(const long long& id, const bool& res);
	void pSiteDeleted(const long long& id, const bool& res);

	void reviewCreated(const long long& id, const bool& res);
	void reviewReaded(const long long& id, const bool& res);
	void reviewUpdated(const long long& id, const bool& res);
	void reviewDeleted(const long long& id, const bool& res);

	void mediaCreated(const long long& id, const bool& res);
	void mediaReaded(const long long& id, const bool& res);
	void mediaUpdated(const long long& id, const bool& res);
	void mediaDeleted(const long long& id, const bool& res);

	void placeCreated(const long long& id, const bool& res);
	void placeReaded(const long long& id, const bool& res);
	void placeUpdated(const long long& id, const bool& res);
	void placeDeleted(const long long& id, const bool& res);
};