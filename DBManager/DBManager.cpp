#include "DBManager.h"

DBManager::DBManager(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	stackedWidget = ui.stackedWidget;
	if (!stackedWidget)
		qDebug() << "Could not load stacked widget!";
	else
	{
		if (stackedWidget)
			stackedWidget->setCurrentIndex(0);

		// Fill vector of empty values
		for (int i = 0; i <= ENT::Database; i++)
		{
			widgetStruct ws;
			w.append(ws);
		}

		// load an mane page
		mainPage = stackedWidget->findChild<QWidget*>("mainPage");

		if (!mainPage)
			qDebug() << "Could not load stacked widget!";
		else
		{
			// Fill every struct
			w[ENT::Tag].baseWidget = stackedWidget->findChild<QWidget*>("createTagWidget");
			w[ENT::Tag].openButton = mainPage->findChild<QPushButton*>("createTagButton");
			if (w.at(ENT::Tag).baseWidget)
			{
				w[ENT::Tag].createButton = w.at(ENT::Tag).baseWidget->findChild<QPushButton*>("createTag");
				w[ENT::Tag].goBackButton = w.at(ENT::Tag).baseWidget->findChild<QPushButton*>("gobackTag");
			}
			else
				qDebug() << "Could not load tag widget!";


			w[ENT::User].baseWidget = stackedWidget->findChild<QWidget*>("createUserWidget");
			w[ENT::User].openButton = mainPage->findChild<QPushButton*>("createUserButton");
			if (w.at(ENT::User).baseWidget)
			{
				w[ENT::User].createButton = w.at(ENT::User).baseWidget->findChild<QPushButton*>("createUser");
				w[ENT::User].goBackButton = w.at(ENT::User).baseWidget->findChild<QPushButton*>("gobackUser");
			}
			else
				qDebug() << "Could not load user widget!";


			w[ENT::Event].baseWidget = stackedWidget->findChild<QWidget*>("createEventWidget");
			w[ENT::Event].openButton = mainPage->findChild<QPushButton*>("createEventButton");
			if (w.at(ENT::Event).baseWidget)
			{
				w[ENT::Event].createButton = w.at(ENT::Event).baseWidget->findChild<QPushButton*>("createEvent");
				w[ENT::Event].goBackButton = w.at(ENT::Event).baseWidget->findChild<QPushButton*>("gobackEvent");
			}
			else
				qDebug() << "Could not load event widget!";


			w[ENT::PSite].baseWidget = stackedWidget->findChild<QWidget*>("createPSiteWidget");
			w[ENT::PSite].openButton = mainPage->findChild<QPushButton*>("createPSiteButton");
			if (w.at(ENT::PSite).baseWidget)
			{
				w[ENT::PSite].createButton = w.at(ENT::PSite).baseWidget->findChild<QPushButton*>("createPSite");
				w[ENT::PSite].goBackButton = w.at(ENT::PSite).baseWidget->findChild<QPushButton*>("gobackPSite");
			}
			else
				qDebug() << "Could not load psite widget!";


			w[ENT::Review].baseWidget = stackedWidget->findChild<QWidget*>("createReviewWidget");
			w[ENT::Review].openButton = mainPage->findChild<QPushButton*>("createReviewButton");
			if (w.at(ENT::Review).baseWidget)
			{
				w[ENT::Review].createButton = w.at(ENT::Review).baseWidget->findChild<QPushButton*>("createReview");
				w[ENT::Review].goBackButton = w.at(ENT::Review).baseWidget->findChild<QPushButton*>("gobackReview");
				/*QStandardItemModel* model = new QStandardItemModel();
				w.at(ENT::Review).baseWidget->findChild<QComboBox*>("WhoAddedEdit")->setModel(model);

				// TEST
				QStandardItem* item0 = new QStandardItem("Test0");
				item0->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
				item0->setData(Qt::Unchecked, Qt::CheckStateRole);

				QStandardItem* item1 = new QStandardItem("Test1");
				item0->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
				item0->setData(Qt::Unchecked, Qt::CheckStateRole);
				//model->setItem(i, 0, item);
				QStandardItemModel* m = (QStandardItemModel*)(w.at(ENT::Review).baseWidget->findChild<QComboBox*>("WhoAddedEdit")->model());
				if (m)
				{
					m->appendRow(item0);
					m->appendRow(item1);
				}*/

			}
			else
				qDebug() << "Could not load review widget!";


			w[ENT::Media].baseWidget = stackedWidget->findChild<QWidget*>("createMediaWidget");
			w[ENT::Media].openButton = mainPage->findChild<QPushButton*>("createMediaButton");
			if (w.at(ENT::Media).baseWidget)
			{
				w[ENT::Media].createButton = w.at(ENT::Media).baseWidget->findChild<QPushButton*>("createMedia");
				w[ENT::Media].goBackButton = w.at(ENT::Media).baseWidget->findChild<QPushButton*>("gobackMedia");
			}
			else
				qDebug() << "Could not load media widget!";


			w[ENT::Place].baseWidget = stackedWidget->findChild<QWidget*>("createPlaceWidget");
			w[ENT::Place].openButton = mainPage->findChild<QPushButton*>("createPlaceButton");
			if (w.at(ENT::Place).baseWidget)
			{
				w[ENT::Place].createButton = w.at(ENT::Place).baseWidget->findChild<QPushButton*>("createPlace");
				w[ENT::Place].goBackButton = w.at(ENT::Place).baseWidget->findChild<QPushButton*>("gobackPlace");
			}
			else
				qDebug() << "Could not load place widget!";


			w[ENT::Database].baseWidget = stackedWidget->findChild<QWidget*>("dbTestWidget");
			w[ENT::Database].openButton = mainPage->findChild<QPushButton*>("dbTestButton");
			if (w.at(ENT::Database).baseWidget)
			{
				w[ENT::Database].createButton = w.at(ENT::Database).baseWidget->findChild<QPushButton*>("testDb");
				w[ENT::Database].goBackButton = w.at(ENT::Database).baseWidget->findChild<QPushButton*>("gobackDb");
				logField = w.at(ENT::Database).baseWidget->findChild<QPlainTextEdit*>("logEdit");
				tasksTable = w.at(ENT::Database).baseWidget->findChild<QTableWidget*>("tasksTable");
			}
			else
				qDebug() << "Could not load database widget!";
			// bind slots to buttons
			bindAllButtons();
		}
	}
	//if (stackedWidget)
		//stackedWidget->setEnabled(false);
}

void DBManager::run(QPointer<DBHandler> dbClass, QPointer<DataValidator> testClass)
{
	validator = testClass;
	dbHandler = dbClass;

	connectAll();

	tasks.append(Task(ENT::Tag, TASK_TYPE::Read, 0));
	emit readTag();

	tasks.append(Task(ENT::User, TASK_TYPE::Read, 0));
	emit readUser();

	tasks.append(Task(ENT::Event, TASK_TYPE::Read, 0));
	emit readEvent();

	tasks.append(Task(ENT::PSite, TASK_TYPE::Read, 0));
	emit readPSite();

	tasks.append(Task(ENT::Review, TASK_TYPE::Read, 0));
	emit readReview();

	tasks.append(Task(ENT::Media, TASK_TYPE::Read, 0));
	emit readMedia();

	tasks.append(Task(ENT::Place, TASK_TYPE::Read, 0));
	emit readPlace();
}

void DBManager::connectAll()
{
	if (dbHandler)
	{
		QObject::connect(this, &DBManager::createTag, dbHandler.data(), &DBHandler::createTag);
		QObject::connect(this, SIGNAL(readTag()), dbHandler.data(), SLOT(readTag()));
		QObject::connect(this, SIGNAL(readTag(const long long&)), dbHandler.data(), SLOT(readTag(const long long&)));
		QObject::connect(this, &DBManager::updateTag, dbHandler.data(), &DBHandler::updateTag);
		QObject::connect(this, &DBManager::deleteTag, dbHandler.data(), &DBHandler::deleteTag);

		QObject::connect(this, &DBManager::createUser, dbHandler.data(), &DBHandler::createUser);
		QObject::connect(this, SIGNAL(readUser()), dbHandler.data(), SLOT(readUser()));
		QObject::connect(this, SIGNAL(readUser(const long long&)), dbHandler.data(), SLOT(readUser(const long long&)));
		QObject::connect(this, &DBManager::updateUser, dbHandler.data(), &DBHandler::updateUser);
		QObject::connect(this, &DBManager::deleteUser, dbHandler.data(), &DBHandler::deleteUser);

		QObject::connect(this, &DBManager::createEvent, dbHandler.data(), &DBHandler::createEvent);
		QObject::connect(this, SIGNAL(readEvent()), dbHandler.data(), SLOT(readEvent()));
		QObject::connect(this, SIGNAL(readEvent(const long long&)), dbHandler.data(), SLOT(readEvent(const long long&)));
		QObject::connect(this, &DBManager::updateEvent, dbHandler.data(), &DBHandler::updateEvent);
		QObject::connect(this, &DBManager::deleteEvent, dbHandler.data(), &DBHandler::deleteEvent);

		QObject::connect(this, &DBManager::createPSite, dbHandler.data(), &DBHandler::createPSite);
		QObject::connect(this, SIGNAL(readPSite()), dbHandler.data(), SLOT(readPSite()));
		QObject::connect(this, SIGNAL(readPSite(const long long&)), dbHandler.data(), SLOT(readPSite(const long long&)));
		QObject::connect(this, &DBManager::updatePSite, dbHandler.data(), &DBHandler::updatePSite);
		QObject::connect(this, &DBManager::deletePSite, dbHandler.data(), &DBHandler::deletePSite);

		QObject::connect(this, &DBManager::createReview, dbHandler.data(), &DBHandler::createReview);
		QObject::connect(this, SIGNAL(readReview()), dbHandler.data(), SLOT(readReview()));
		QObject::connect(this, SIGNAL(readReview(const long long&)), dbHandler.data(), SLOT(readReview(const long long&)));
		QObject::connect(this, &DBManager::updateReview, dbHandler.data(), &DBHandler::updateReview);
		QObject::connect(this, &DBManager::deleteReview, dbHandler.data(), &DBHandler::deleteReview);

		QObject::connect(this, &DBManager::createMedia, dbHandler.data(), &DBHandler::createMedia);
		QObject::connect(this, SIGNAL(readMedia()), dbHandler.data(), SLOT(readMedia()));
		QObject::connect(this, SIGNAL(readMedia(const long long&)), dbHandler.data(), SLOT(readMedia(const long long&)));
		QObject::connect(this, &DBManager::updateMedia, dbHandler.data(), &DBHandler::updateMedia);
		QObject::connect(this, &DBManager::deleteMedia, dbHandler.data(), &DBHandler::deleteMedia);

		QObject::connect(this, &DBManager::createPlace, dbHandler.data(), &DBHandler::createPlace);
		QObject::connect(this, SIGNAL(readPlace()), dbHandler.data(), SLOT(readPlace()));
		QObject::connect(this, SIGNAL(readPlace(const long long&)), dbHandler.data(), SLOT(readPlace(const long long&)));
		QObject::connect(this, &DBManager::updatePlace, dbHandler.data(), &DBHandler::updatePlace);
		QObject::connect(this, &DBManager::deletePlace, dbHandler.data(), &DBHandler::deletePlace);

		QObject::connect(dbHandler.data(), &DBHandler::haveAnError, this, &DBManager::haveAnError);

		QObject::connect(dbHandler.data(), &DBHandler::hasEvent, this, &DBManager::hasEvent);
		QObject::connect(dbHandler.data(), &DBHandler::hasPlace, this, &DBManager::hasPlace);
		QObject::connect(dbHandler.data(), &DBHandler::hasMedia, this, &DBManager::hasMedia);
		QObject::connect(dbHandler.data(), &DBHandler::hasUser, this, &DBManager::hasUser);
		QObject::connect(dbHandler.data(), &DBHandler::hasPSite, this, &DBManager::hasPSite);
		QObject::connect(dbHandler.data(), &DBHandler::hasTag, this, &DBManager::hasTag);
		QObject::connect(dbHandler.data(), &DBHandler::hasReview, this, &DBManager::hasReview);

		QObject::connect(dbHandler.data(), &DBHandler::tagCreated, this, &DBManager::tagCreated);
		QObject::connect(dbHandler.data(), &DBHandler::tagReaded, this, &DBManager::tagReaded);
		QObject::connect(dbHandler.data(), &DBHandler::tagUpdated, this, &DBManager::tagUpdated);
		QObject::connect(dbHandler.data(), &DBHandler::tagDeleted, this, &DBManager::tagDeleted);

		QObject::connect(dbHandler.data(), &DBHandler::tagDeleted, this, &DBManager::tagDeleted);
		QObject::connect(dbHandler.data(), &DBHandler::userReaded, this, &DBManager::userReaded);
		QObject::connect(dbHandler.data(), &DBHandler::userUpdated, this, &DBManager::userUpdated);
		QObject::connect(dbHandler.data(), &DBHandler::userDeleted, this, &DBManager::userDeleted);

		QObject::connect(dbHandler.data(), &DBHandler::eventCreated, this, &DBManager::eventCreated);
		QObject::connect(dbHandler.data(), &DBHandler::eventReaded, this, &DBManager::eventReaded);
		QObject::connect(dbHandler.data(), &DBHandler::eventUpdated, this, &DBManager::eventUpdated);
		QObject::connect(dbHandler.data(), &DBHandler::eventDeleted, this, &DBManager::eventDeleted);

		QObject::connect(dbHandler.data(), &DBHandler::pSiteCreated, this, &DBManager::pSiteCreated);
		QObject::connect(dbHandler.data(), &DBHandler::pSiteReaded, this, &DBManager::pSiteReaded);
		QObject::connect(dbHandler.data(), &DBHandler::pSiteUpdated, this, &DBManager::pSiteUpdated);
		QObject::connect(dbHandler.data(), &DBHandler::pSiteDeleted, this, &DBManager::pSiteDeleted);

		QObject::connect(dbHandler.data(), &DBHandler::reviewCreated, this, &DBManager::reviewCreated);
		QObject::connect(dbHandler.data(), &DBHandler::reviewReaded, this, &DBManager::reviewReaded);
		QObject::connect(dbHandler.data(), &DBHandler::reviewUpdated, this, &DBManager::reviewUpdated);
		QObject::connect(dbHandler.data(), &DBHandler::reviewDeleted, this, &DBManager::reviewDeleted);

		QObject::connect(dbHandler.data(), &DBHandler::mediaCreated, this, &DBManager::mediaCreated);
		QObject::connect(dbHandler.data(), &DBHandler::mediaReaded, this, &DBManager::mediaReaded);
		QObject::connect(dbHandler.data(), &DBHandler::mediaUpdated, this, &DBManager::mediaUpdated);
		QObject::connect(dbHandler.data(), &DBHandler::mediaDeleted, this, &DBManager::mediaDeleted);

		QObject::connect(dbHandler.data(), &DBHandler::placeCreated, this, &DBManager::placeCreated);
		QObject::connect(dbHandler.data(), &DBHandler::placeReaded, this, &DBManager::placeReaded);
		QObject::connect(dbHandler.data(), &DBHandler::placeUpdated, this, &DBManager::placeUpdated);
		QObject::connect(dbHandler.data(), &DBHandler::placeDeleted, this, &DBManager::placeDeleted);
	}
}

void DBManager::disconnectAll()
{
	if (dbHandler)
	{
		QObject::disconnect(this, &DBManager::createTag, dbHandler.data(), &DBHandler::createTag);
		QObject::disconnect(this, SIGNAL(readTag()), dbHandler.data(), SLOT(readTag()));
		QObject::disconnect(this, SIGNAL(readTag(const long long&)), dbHandler.data(), SLOT(readTag(const long long&)));
		QObject::disconnect(this, &DBManager::updateTag, dbHandler.data(), &DBHandler::updateTag);
		QObject::disconnect(this, &DBManager::deleteTag, dbHandler.data(), &DBHandler::deleteTag);

		QObject::disconnect(this, &DBManager::createUser, dbHandler.data(), &DBHandler::createUser);
		QObject::disconnect(this, SIGNAL(readUser()), dbHandler.data(), SLOT(readUser()));
		QObject::disconnect(this, SIGNAL(readUser(const long long&)), dbHandler.data(), SLOT(readUser(const long long&)));
		QObject::disconnect(this, &DBManager::updateUser, dbHandler.data(), &DBHandler::updateUser);
		QObject::disconnect(this, &DBManager::deleteUser, dbHandler.data(), &DBHandler::deleteUser);

		QObject::disconnect(this, &DBManager::createEvent, dbHandler.data(), &DBHandler::createEvent);
		QObject::disconnect(this, SIGNAL(readEvent()), dbHandler.data(), SLOT(readEvent()));
		QObject::disconnect(this, SIGNAL(readEvent(const long long&)), dbHandler.data(), SLOT(readEvent(const long long&)));
		QObject::disconnect(this, &DBManager::updateEvent, dbHandler.data(), &DBHandler::updateEvent);
		QObject::disconnect(this, &DBManager::deleteEvent, dbHandler.data(), &DBHandler::deleteEvent);

		QObject::disconnect(this, &DBManager::createPSite, dbHandler.data(), &DBHandler::createPSite);
		QObject::disconnect(this, SIGNAL(readPSite()), dbHandler.data(), SLOT(readPSite()));
		QObject::disconnect(this, SIGNAL(readPSite(const long long&)), dbHandler.data(), SLOT(readPSite(const long long&)));
		QObject::disconnect(this, &DBManager::updatePSite, dbHandler.data(), &DBHandler::updatePSite);
		QObject::disconnect(this, &DBManager::deletePSite, dbHandler.data(), &DBHandler::deletePSite);

		QObject::disconnect(this, &DBManager::createReview, dbHandler.data(), &DBHandler::createReview);
		QObject::disconnect(this, SIGNAL(readReview()), dbHandler.data(), SLOT(readReview()));
		QObject::disconnect(this, SIGNAL(readReview(const long long&)), dbHandler.data(), SLOT(readReview(const long long&)));
		QObject::disconnect(this, &DBManager::updateReview, dbHandler.data(), &DBHandler::updateReview);
		QObject::disconnect(this, &DBManager::deleteReview, dbHandler.data(), &DBHandler::deleteReview);

		QObject::disconnect(this, &DBManager::createMedia, dbHandler.data(), &DBHandler::createMedia);
		QObject::disconnect(this, SIGNAL(readMedia()), dbHandler.data(), SLOT(readMedia()));
		QObject::disconnect(this, SIGNAL(readMedia(const long long&)), dbHandler.data(), SLOT(readMedia(const long long&)));
		QObject::disconnect(this, &DBManager::updateMedia, dbHandler.data(), &DBHandler::updateMedia);
		QObject::disconnect(this, &DBManager::deleteMedia, dbHandler.data(), &DBHandler::deleteMedia);

		QObject::disconnect(this, &DBManager::createPlace, dbHandler.data(), &DBHandler::createPlace);
		QObject::disconnect(this, SIGNAL(readPlace()), dbHandler.data(), SLOT(readPlace()));
		QObject::disconnect(this, SIGNAL(readPlace(const long long&)), dbHandler.data(), SLOT(readPlace(const long long&)));
		QObject::disconnect(this, &DBManager::updatePlace, dbHandler.data(), &DBHandler::updatePlace);
		QObject::disconnect(this, &DBManager::deletePlace, dbHandler.data(), &DBHandler::deletePlace);

		QObject::disconnect(dbHandler.data(), &DBHandler::haveAnError, this, &DBManager::haveAnError);

		QObject::disconnect(dbHandler.data(), &DBHandler::hasEvent, this, &DBManager::hasEvent);
		QObject::disconnect(dbHandler.data(), &DBHandler::hasPlace, this, &DBManager::hasPlace);
		QObject::disconnect(dbHandler.data(), &DBHandler::hasMedia, this, &DBManager::hasMedia);
		QObject::disconnect(dbHandler.data(), &DBHandler::hasUser, this, &DBManager::hasUser);
		QObject::disconnect(dbHandler.data(), &DBHandler::hasPSite, this, &DBManager::hasPSite);
		QObject::disconnect(dbHandler.data(), &DBHandler::hasTag, this, &DBManager::hasTag);
		QObject::disconnect(dbHandler.data(), &DBHandler::hasReview, this, &DBManager::hasReview);

		QObject::disconnect(dbHandler.data(), &DBHandler::tagCreated, this, &DBManager::tagCreated);
		QObject::disconnect(dbHandler.data(), &DBHandler::tagReaded, this, &DBManager::tagReaded);
		QObject::disconnect(dbHandler.data(), &DBHandler::tagUpdated, this, &DBManager::tagUpdated);
		QObject::disconnect(dbHandler.data(), &DBHandler::tagDeleted, this, &DBManager::tagDeleted);

		QObject::disconnect(dbHandler.data(), &DBHandler::tagDeleted, this, &DBManager::tagDeleted);
		QObject::disconnect(dbHandler.data(), &DBHandler::userReaded, this, &DBManager::userReaded);
		QObject::disconnect(dbHandler.data(), &DBHandler::userUpdated, this, &DBManager::userUpdated);
		QObject::disconnect(dbHandler.data(), &DBHandler::userDeleted, this, &DBManager::userDeleted);

		QObject::disconnect(dbHandler.data(), &DBHandler::eventCreated, this, &DBManager::eventCreated);
		QObject::disconnect(dbHandler.data(), &DBHandler::eventReaded, this, &DBManager::eventReaded);
		QObject::disconnect(dbHandler.data(), &DBHandler::eventUpdated, this, &DBManager::eventUpdated);
		QObject::disconnect(dbHandler.data(), &DBHandler::eventDeleted, this, &DBManager::eventDeleted);

		QObject::disconnect(dbHandler.data(), &DBHandler::pSiteCreated, this, &DBManager::pSiteCreated);
		QObject::disconnect(dbHandler.data(), &DBHandler::pSiteReaded, this, &DBManager::pSiteReaded);
		QObject::disconnect(dbHandler.data(), &DBHandler::pSiteUpdated, this, &DBManager::pSiteUpdated);
		QObject::disconnect(dbHandler.data(), &DBHandler::pSiteDeleted, this, &DBManager::pSiteDeleted);

		QObject::disconnect(dbHandler.data(), &DBHandler::reviewCreated, this, &DBManager::reviewCreated);
		QObject::disconnect(dbHandler.data(), &DBHandler::reviewReaded, this, &DBManager::reviewReaded);
		QObject::disconnect(dbHandler.data(), &DBHandler::reviewUpdated, this, &DBManager::reviewUpdated);
		QObject::disconnect(dbHandler.data(), &DBHandler::reviewDeleted, this, &DBManager::reviewDeleted);

		QObject::disconnect(dbHandler.data(), &DBHandler::mediaCreated, this, &DBManager::mediaCreated);
		QObject::disconnect(dbHandler.data(), &DBHandler::mediaReaded, this, &DBManager::mediaReaded);
		QObject::disconnect(dbHandler.data(), &DBHandler::mediaUpdated, this, &DBManager::mediaUpdated);
		QObject::disconnect(dbHandler.data(), &DBHandler::mediaDeleted, this, &DBManager::mediaDeleted);

		QObject::disconnect(dbHandler.data(), &DBHandler::placeCreated, this, &DBManager::placeCreated);
		QObject::disconnect(dbHandler.data(), &DBHandler::placeReaded, this, &DBManager::placeReaded);
		QObject::disconnect(dbHandler.data(), &DBHandler::placeUpdated, this, &DBManager::placeUpdated);
		QObject::disconnect(dbHandler.data(), &DBHandler::placeDeleted, this, &DBManager::placeDeleted);
	}
}

void DBManager::bindAllButtons()
{

	for (int i = 0; i <= ENT::Database; i++)
	{
		if (w.at(i).createButton)
			connect(w[i].createButton, &QPushButton::clicked, this, &DBManager::createButtonClicked);

		if (w.at(i).goBackButton)
			connect(w[i].goBackButton, &QPushButton::clicked, this, &DBManager::goBackButtonClicked);

		if (w.at(i).openButton)
			connect(w[i].openButton, &QPushButton::clicked, this, &DBManager::openButtonClicked);
	}

	if (tasksTable)
	{
		connect(&tasks, &VectorWrapper::removed, this, &DBManager::taskRemoved);
		connect(&tasks, &VectorWrapper::inserted, this, &DBManager::taskInserted);
	}
}

template <typename T>
long long DBManager::getLastId(const QVector<T>& data)
{
	long long lastId = 0;
	for (const T& foo : data)
		if (foo.ID >= lastId)
			lastId = foo.ID + 1;
	return lastId;
}

template <typename T>
bool DBManager::checkName(const QVector<T>& data, const QString& name)
{
	for (const T& foo : data)
		if (foo.Name.compare(name) == 0)
			return false;
	return true;
}

template <typename T>
bool DBManager::removeValue(QVector<T>& data, const long long& id)
{
	for (size_t i = 0; i < data.size(); i++)
		if (data.at(i).ID == id)
		{
			data.removeAt(i);
			return true;
		}
	return false;
}

void DBManager::openButtonClicked()
{
	QPointer<QPushButton> btn = dynamic_cast<QPushButton*>(QObject::sender());

	bool found = false;
	if (btn)
		for (int i = 0; i <= ENT::Database; i++)
			if (w.at(i).openButton == btn)
			{
				found = true;
				if (stackedWidget)
					stackedWidget->setCurrentIndex(i + 1);
			}


	if (!found)
		log("Could not detect sender button");
}

void DBManager::createButtonClicked()
{
	QPointer<QPushButton> btn = dynamic_cast<QPushButton*>(QObject::sender());

	if (btn)
		if (w.at(ENT::Database).createButton == btn)
			testDatabase();
		else if (w.at(ENT::Event).createButton == btn)
			fetchEvent();
		else if (w.at(ENT::Media).createButton == btn)
			fetchMedia();
		else if (w.at(ENT::Place).createButton == btn)
			fetchPlace();
		else if (w.at(ENT::PSite).createButton == btn)
			fetchPSite();
		else if (w.at(ENT::Review).createButton == btn)
			fetchReview();
		else if (w.at(ENT::Tag).createButton == btn)
			fetchTag();
		else if (w.at(ENT::User).createButton == btn)
			fetchUser();
}

void DBManager::taskRemoved(const size_t& pos)
{
	if (tasksTable)
		if (tasksTable->rowCount() > pos)
			tasksTable->removeRow(pos);
}

void DBManager::taskInserted(const Task& data)
{
	if (tasksTable)
	{
		QTableWidgetItem* t1 = new QTableWidgetItem(Task::objName(data.obj));
		QTableWidgetItem* t2 = new QTableWidgetItem(Task::typeName(data.type));
		QTableWidgetItem* t3 = new QTableWidgetItem(QString::number(data.objId));

		int rowCount = tasksTable->rowCount();
		tasksTable->setRowCount(rowCount + 1);
		tasksTable->setItem(rowCount, 0, t1);
		tasksTable->setItem(rowCount, 1, t2);
		tasksTable->setItem(rowCount, 2, t3);
	}
}

void DBManager::fetchUser()
{
	const QPointer<QWidget> baseWidget = w.at(ENT::User).baseWidget;
	if (baseWidget)
	{
		QPointer<QLineEdit> nameEdit = baseWidget->findChild<QLineEdit*>("NameEdit");
		QPointer<QLineEdit> surnameEdit = baseWidget->findChild<QLineEdit*>("SurnameEdit");
		QPointer<QPlainTextEdit> contactsEdit = baseWidget->findChild<QPlainTextEdit*>("ContactsEdit");
		QPointer<QLineEdit> loginEdit = baseWidget->findChild<QLineEdit*>("LoginEdit");
		QPointer<QLineEdit> avatarEdit = baseWidget->findChild<QLineEdit*>("AvatarEdit");
		QPointer<QLineEdit> passwordEdit = baseWidget->findChild<QLineEdit*>("PasswordEdit");

		dbUser u;
		bool ok = true;

		if (nameEdit && surnameEdit && contactsEdit && loginEdit && passwordEdit && avatarEdit)
		{
			u.Name = nameEdit->text();
			u.Surname = surnameEdit->text();
			u.Contacts = contactsEdit->toPlainText().split('\n', QString::SplitBehavior::SkipEmptyParts);
			u.Login = loginEdit->text();
			u.PassHash = hash(passwordEdit->text());
			u.Userpic = avatarEdit->text();
		}
		else
			ok = false;

		// Check if user not existss and get last id
		long long lastId = 0;
		if (ok)
			for (const dbUser& foo : db.users)
			{
				if (foo.Login.compare(u.Login) == 0)
					ok = false;
				if (foo.ID >= lastId)
					lastId = foo.ID + 1;
			}

		if (ok)
		{
			u.ID = lastId;
			u.CreatedAt = QDateTime::currentDateTime();
			u.UpdatedAt = u.CreatedAt;
			if (u.isValid())
			{
				db.users.append(u);
				emit createUser(u);
				tasks.append(Task(ENT::User, TASK_TYPE::Create, u.ID));
				baseWidget->setEnabled(false);
			}
			else
				ok = false;
		}
		if (!ok)
			showAlert("Не удалось создать пользователя!");
	}
}

void DBManager::fetchReview()
{
	const QPointer<QWidget> baseWidget = w.at(ENT::Review).baseWidget;
	if (baseWidget)
	{
		QPointer<QPlainTextEdit> textEdit = baseWidget->findChild<QPlainTextEdit*>("plainTextEdit");
		QPointer<QLineEdit> rateEdit = baseWidget->findChild<QLineEdit*>("RateEdit");
		QPointer<ListBox> userCBox = baseWidget->findChild<ListBox*>("WhoAddedEdit");

		dbReview u;
		bool ok = true;

		if (textEdit && rateEdit && userCBox)
		{
			u.Text = textEdit->toPlainText();
			u.Rate = rateEdit->text();
			u.Users = userCBox->getAllCheckedItemIds();
		}
		else
			ok = false;

		long long lastId = 0;
		if (ok)
			for (const dbReview& foo : db.reviews)
			{
				if (foo.Text.compare(u.Text) == 0)
					ok = false;
				if (foo.ID > lastId)
					lastId = foo.ID + 1;
			}

		if (ok)
		{
			u.ID = lastId;
			u.CreatedAt = QDateTime::currentDateTime();
			u.UpdatedAt = u.CreatedAt;
			u.AddTime = u.CreatedAt;
			if (u.isValid())
			{
				db.reviews.append(u);
				emit createReview(u);
				tasks.append(Task(ENT::Review, TASK_TYPE::Create, u.ID));
				baseWidget->setEnabled(false);
			}
			else
				ok = false;
		}
		if (!ok)
			showAlert("Не удалось создать обзор!");
	}
}

void DBManager::fetchPSite()
{
	const QPointer<QWidget> baseWidget = w.at(ENT::PSite).baseWidget;
	if (baseWidget)
	{
		QPointer<QLineEdit> linkEdit = baseWidget->findChild<QLineEdit*>("RefEdit");
		QPointer<QPlainTextEdit> textEdit = baseWidget->findChild<QPlainTextEdit*>("DefEdit");

		dbPartnerSite ps;
		bool ok = true;

		if (linkEdit && textEdit)
		{
			ps.Ref = linkEdit->text();
			ps.Def = textEdit->toPlainText();
		}
		else
			ok = false;

		// Check if tag not existss and get last id
		if (ps.Ref.length() == 0)
			ok = false;

		long long lastId = 0;
		if (ok)
			for (const dbPartnerSite& foo : db.partnerSites)
			{
				if (foo.Ref.compare(ps.Ref) == 0)
					ok = false;
				if (foo.ID > lastId)
					lastId = foo.ID + 1;
			}

		if (ok)
		{
			ps.ID = lastId;
			ps.CreatedAt = QDateTime::currentDateTime();
			ps.UpdatedAt = ps.CreatedAt;
			if (ps.isValid())
			{
				db.partnerSites.append(ps);
				emit createPSite(ps);
				tasks.append(Task(ENT::PSite, TASK_TYPE::Create, ps.ID));
				baseWidget->setEnabled(false);
			}
			else
				ok = false;
		}
		else
			showAlert("Не удалось создать партнерский сайт!");
	}
}

void DBManager::fetchPlace()
{
	const QPointer<QWidget> baseWidget = w.at(ENT::Place).baseWidget;
	if (baseWidget)
	{
		QPointer<QLineEdit> coordXEdit = baseWidget->findChild<QLineEdit*>("CoordXEdit");
		QPointer<QLineEdit> coordYEdit = baseWidget->findChild<QLineEdit*>("CoordYEdit");
		QPointer<QPlainTextEdit> descrFiled = baseWidget->findChild<QPlainTextEdit*>("Def_2_Edit");
		QPointer<ListBox> mediaComboBox = baseWidget->findChild<ListBox*>("MediaEdit_2");
		QPointer<QLineEdit> nameField = baseWidget->findChild<QLineEdit*>("NameEdit_3");
		QPointer<QPlainTextEdit> addrField = baseWidget->findChild<QPlainTextEdit*>("PlaceAddrEdit");

		dbPlace pl;
		bool ok = true;

		if (coordXEdit && coordYEdit && descrFiled && mediaComboBox && nameField && addrField)
		{
			pl.Name = nameField->text();
			pl.Descr = descrFiled->toPlainText();
			pl.CoordX = coordXEdit->text().toDouble();
			pl.CoordY = coordYEdit->text().toDouble();
			pl.Address = addrField->toPlainText();

			QVector<long long> Media;//     pq.Int64Array `gorm:"type:bigint[]" json:"media"`
		}
		else
			ok = false;

		const long long lastId = getLastId<dbPlace>(db.places);
		ok = checkName<dbPlace>(db.places, pl.Name);

		if (ok)
		{
			pl.ID = lastId;
			pl.CreatedAt = QDateTime::currentDateTime();
			pl.UpdatedAt = pl.CreatedAt;
			if (pl.isValid())
			{
				db.places.append(pl);
				emit createPlace(pl);
				tasks.append(Task(ENT::Place, TASK_TYPE::Create, pl.ID));
				baseWidget->setEnabled(false);
			}
			else
				ok = false;
		}
		else
			showAlert("Не удалось добавить место!");
	}
}

void DBManager::fetchMedia()
{
	const QPointer<QWidget> baseWidget = w.at(ENT::Media).baseWidget;
	if (baseWidget)
	{
		QPointer<QLineEdit> nameEdit = baseWidget->findChild<QLineEdit*>("NameEdit_2");
		QPointer<QLineEdit> rateEdit = baseWidget->findChild<QLineEdit*>("RateEdit_3");
		QPointer<QPlainTextEdit> referencesEdit = baseWidget->findChild<QPlainTextEdit*>("RefsEdit");
		QPointer<QPlainTextEdit> descrEdit = baseWidget->findChild<QPlainTextEdit*>("plainTextEdit_2");

		dbMedia m;
		bool ok = true;

		if (nameEdit && rateEdit && referencesEdit && descrEdit)
		{
			m.Name = nameEdit->text();
			m.Rate = rateEdit->text().toLongLong();
			m.References = QStringList(referencesEdit->toPlainText());// pq.StringArray `gorm:"type:text[]" json:"refs"`
			m.Descr = descrEdit->toPlainText();//string `json:"descr"`

		}
		else
			ok = false;

		// Check if tag not existss and get last id
		if (m.Name.length() == 0)
			ok = false;

		const long long lastId = getLastId<dbMedia>(db.medias);
		ok = checkName<dbMedia>(db.medias, m.Name);

		if (ok)
		{
			m.ID = lastId;
			m.CreatedAt = QDateTime::currentDateTime();
			m.UpdatedAt = m.CreatedAt;
			if (m.isValid())
			{
				db.medias.append(m);
				emit createMedia(m);
				tasks.append(Task(ENT::Media, TASK_TYPE::Create, m.ID));
				baseWidget->setEnabled(false);
			}
			else
				ok = false;
		}
		else
			showAlert("Не удалось создать медиа!");
	}
}

void DBManager::fetchTag()
{
	const QPointer<QWidget> baseWidget = w.at(ENT::Tag).baseWidget;
	if (baseWidget)
	{
		QPointer<QLineEdit> nameEdit = baseWidget->findChild<QLineEdit*>("TagNameEdit");

		dbTag u;
		bool ok = true;

		if (nameEdit)
			u.Name = nameEdit->text();
		else
			ok = false;

		// Check if tag not existss and get last id
		if (u.Name.length() == 0)
			ok = false;

		const long long lastId = getLastId<dbTag>(db.tags);
		ok = checkName<dbTag>(db.tags, u.Name);

		if (ok)
		{
			u.ID = lastId;
			u.CreatedAt = QDateTime::currentDateTime();
			u.UpdatedAt = u.CreatedAt;
			if (u.isValid())
			{
				db.tags.append(u);
				emit createTag(u);
				tasks.append(Task(ENT::Tag, TASK_TYPE::Create, u.ID));
				baseWidget->setEnabled(false);
			}
			else
				ok = false;
		}
		else
			showAlert("Не удалось создать тег!");
	}
}

void DBManager::fetchEvent()
{
	const QPointer<QWidget> baseWidget = w.at(ENT::Event).baseWidget;
	if (baseWidget)
	{
		QPointer<QLineEdit> nameEdit = baseWidget->findChild<QLineEdit*>("nameEdit");
		QPointer<QLineEdit> extra1Edit = baseWidget->findChild<QLineEdit*>("Ex1Edit");
		QPointer<QLineEdit> extra2Edit = baseWidget->findChild<QLineEdit*>("Ex2Edit");
		QPointer<QLineEdit> fullDescrEdit = baseWidget->findChild<QLineEdit*>("FullDescrEdit");
		QPointer<ListBox> mediaComboBox = baseWidget->findChild<ListBox*>("MediaEdit");
		QPointer<ListBox> pSiteCombox = baseWidget->findChild<ListBox*>("PSiteEdit");
		QPointer<ListBox> placeCombobox = baseWidget->findChild<ListBox*>("PlaceEdit");
		QPointer<ListBox> reviewsCombobox = baseWidget->findChild<ListBox*>("RevEdit");
		QPointer<ListBox> usersCombobox = baseWidget->findChild<ListBox*>("UsersEdit");
		QPointer<ListBox> tagBox = baseWidget->findChild<ListBox*>("tagBox");
		QPointer<QLineEdit> rateEdit = baseWidget->findChild<QLineEdit*>("RateEdit_2");
		QPointer<QLineEdit> routeEdit = baseWidget->findChild<QLineEdit*>("RouteEdit");
		QPointer<QLineEdit> shortDescrEdit = baseWidget->findChild<QLineEdit*>("ShDescrEdit");
		QPointer<QPlainTextEdit> timteable = baseWidget->findChild<QPlainTextEdit*>("TimetableEdit");

		dbEvent e;
		bool ok = true;

		if (nameEdit && tagBox && extra1Edit && extra2Edit && fullDescrEdit && mediaComboBox && pSiteCombox && placeCombobox && reviewsCombobox && usersCombobox && rateEdit && routeEdit && shortDescrEdit && timteable)
		{
			e.Name = nameEdit->text();
			e.ShDescr = shortDescrEdit->text();
			e.FullDescr = fullDescrEdit->text();
			e.Routing = routeEdit->text();
			e.Places = placeCombobox->getAllCheckedItemIds();
			e.Users = usersCombobox->getAllCheckedItemIds();
			e.Tags = tagBox->getAllCheckedItemIds();
			e.Rate = rateEdit->text().toLongLong();
			e.Reviews = reviewsCombobox->getAllCheckedItemIds();
			e.PartnerSite = pSiteCombox->getAllCheckedItemIds();
			e.Media = mediaComboBox->getAllCheckedItemIds();
			e.Timetable = parseTimeTable(timteable->toPlainText().split('\n'));
			e.Extra1 = extra1Edit->text();
			e.Extra2 = extra2Edit->text();
		}
		else
			ok = false;

		const long long lastId = getLastId<dbEvent>(db.events);
		ok = checkName<dbEvent>(db.events, e.Name);

		if (ok)
		{
			e.ID = lastId;
			e.CreatedAt = QDateTime::currentDateTime();
			e.UpdatedAt = e.CreatedAt;
			if (e.isValid())
			{
				db.events.append(e);
				emit createEvent(e);
				tasks.append(Task(ENT::Event, TASK_TYPE::Create, e.ID));
				baseWidget->setEnabled(false);
			}
			else
				ok = false;
		}
		else
			showAlert("Не удалось создать событие!");
	}
}

void DBManager::goBackButtonClicked()
{
	if (stackedWidget)
		stackedWidget->setCurrentIndex(0);
}

void DBManager::log(const QString& t)
{
	if (logField)
		logField->appendPlainText(t);
}

void DBManager::showAlert(const QString& text)
{
	log(text);
	QMessageBox msgBox;
	msgBox.setText(text);
	msgBox.exec();
}

QStringList DBManager::parseTimeTable(const QStringList& src)
{
	QStringList res;
	for (const QString& s : src)
	{
		if (s.compare(DATE_PERIOD_PERIODIC_FLAG) == 0)
		{
			res.append(DATE_PERIOD_PERIODIC_FLAG);
			break;
		}
		else
		{
			QString bar = s;
			bar = bar.replace(" ", "");
			const QStringList foo = s.split(DATE_PERIOD_DIV);
			if (foo.size() < 2)
				showAlert("Временной интервал задан неправильно: " + s);
			else
			{
				const QDateTime t1 = QDateTime::fromString(foo.at(0), DATE_PERIOD_PARSE_FORMAT);
				const QDateTime t2 = QDateTime::fromString(foo.at(1), DATE_PERIOD_PARSE_FORMAT);
				if (!(t1.isValid() && t2.isValid()))
					showAlert("Время невалидно: " + s);
				else
				{
					res.append(t1.toString(DATE_PERIOD_FORMAT));
					res.append(t2.toString(DATE_PERIOD_FORMAT));
				}
			}
		}
	}
	return res;
}

void DBManager::addUserIntoAllFileds(const dbUser& u)
{
	const QPointer<QWidget> baseWidget0 = w.at(ENT::Review).baseWidget;
	if (baseWidget0)
	{
		QPointer<ListBox> userCBox = baseWidget0->findChild<ListBox*>("WhoAddedEdit");
		if (userCBox)
			userCBox->addCheckItem(u.Name, u.Surname, Qt::CheckState::Unchecked, u.ID);
	}
}

void DBManager::addMediaIntoAllFileds(const dbMedia& m)
{
	const QPointer<QWidget> baseWidget0 = w.at(ENT::Event).baseWidget;
	if (baseWidget0)
	{
		QPointer<ListBox> mediaComboBox = baseWidget0->findChild<ListBox*>("MediaEdit");
		if (mediaComboBox)
			mediaComboBox->addCheckItem(m.Name, m.Descr, Qt::CheckState::Unchecked, m.ID);
	}
	const QPointer<QWidget> baseWidget1 = w.at(ENT::Place).baseWidget;
	if (baseWidget1)
	{
		QPointer<ListBox> mediaComboBox = baseWidget1->findChild<ListBox*>("MediaEdit_2");
		if (mediaComboBox)
			mediaComboBox->addCheckItem(m.Name, m.Descr, Qt::CheckState::Unchecked, m.ID);
	}
}

void DBManager::addPSiteIntoAllFileds(const dbPartnerSite& ps)
{
	const QPointer<QWidget> baseWidget0 = w.at(ENT::Event).baseWidget;
	if (baseWidget0)
	{
		QPointer<ListBox> pSiteCombox = baseWidget0->findChild<ListBox*>("PSiteEdit");
		if (pSiteCombox)
			pSiteCombox->addCheckItem(ps.Ref, ps.Def, Qt::CheckState::Unchecked, ps.ID);
	}
}

void DBManager::addPlaceIntoAllFileds(const dbPlace& pl)
{
	const QPointer<QWidget> baseWidget1 = w.at(ENT::Event).baseWidget;
	if (baseWidget1)
	{
		QPointer<ListBox> placeCombobox = baseWidget1->findChild<ListBox*>("PlaceEdit");
		if (placeCombobox)
			placeCombobox->addCheckItem(pl.Name, pl.Descr, Qt::CheckState::Unchecked, pl.ID);
	}
}

void DBManager::addReviewIntoAllFileds(const dbReview& r)
{
	const QPointer<QWidget> baseWidget0 = w.at(ENT::Event).baseWidget;
	if (baseWidget0)
	{
		QPointer<ListBox> reviewsCombobox = baseWidget0->findChild<ListBox*>("RevEdit");
		if (reviewsCombobox)
			reviewsCombobox->addCheckItem(r.AddTime.toString(DATE_TIME_FORMAT), r.Rate, Qt::CheckState::Unchecked, r.ID);
	}
}

void DBManager::addTagIntoAllFileds(const dbTag& t)
{
	const QPointer<QWidget> baseWidget0 = w.at(ENT::Event).baseWidget;
	if (baseWidget0)
	{
		QPointer<ListBox> tagBox = baseWidget0->findChild<ListBox*>("tagBox");
		if (tagBox)
			tagBox->addCheckItem(t.Name, t.ID, Qt::CheckState::Unchecked, t.ID);
	}
}

void DBManager::taskFinished(const ENT& _obj, const TASK_TYPE& _type, const long long& _objId)
{
	bool found = false;
	for (size_t i = 0; i < tasks.size(); i++)
		if (tasks.at(i).obj == _obj && tasks.at(i).type == _type && tasks.at(i).objId == _objId)
		{
			found = true;
			tasks.removeAt(i);
			break;
		}
	if (!found)
		showAlert("Завершено невалидное задание: " + Task(_obj, _type, _objId).toString());
	log("Завершено задание: " + Task(_obj, _type, _objId).toString());
}

////////////////////////////////////////////////////////////////
//				ANSWER HANDLERS
////////////////////////////////////////////////////////////////

void DBManager::hasEvent(const dbEvent& data)
{
	bool foo = true;
	for (int i = 0; i < db.events.size(); i++)
	{
		if (db.events.at(i).ID == data.ID)
		{
			db.events[i] = data;
			foo = false;
			break;
		}
	}
	if (foo)
		db.events.append(data);
}

void DBManager::hasPlace(const dbPlace& data)
{
	bool foo = true;
	for (int i = 0; i < db.places.size(); i++)
	{
		if (db.places.at(i).ID == data.ID)
		{
			db.places[i] = data;
			foo = false;
			break;
		}
	}
	if (foo)
	{
		db.places.append(data);
		addPlaceIntoAllFileds(data);
	}
}

void DBManager::hasMedia(const dbMedia& data)
{
	bool foo = true;
	for (int i = 0; i < db.medias.size(); i++)
	{
		if (db.medias.at(i).ID == data.ID)
		{
			db.medias[i] = data;
			foo = false;
			break;
		}
	}
	if (foo)
	{
		db.medias.append(data);
		addMediaIntoAllFileds(data);
	}
}


void DBManager::hasUser(const dbUser& data)
{
	bool foo = true;
	for (int i = 0; i < db.users.size(); i++)
	{
		if (db.users.at(i).ID == data.ID)
		{
			db.users[i] = data;
			foo = false;
			break;
		}
	}
	if (foo)
	{
		db.users.append(data);
		addUserIntoAllFileds(data);
	}
}

void DBManager::hasPSite(const dbPartnerSite& data)
{
	bool foo = true;
	for (int i = 0; i < db.partnerSites.size(); i++)
	{
		if (db.partnerSites.at(i).ID == data.ID)
		{
			db.partnerSites[i] = data;
			foo = false;
			break;
		}
	}
	if (foo)
	{
		db.partnerSites.append(data);
		addPSiteIntoAllFileds(data);
	}
}

void DBManager::hasTag(dbTag data)
{
	bool foo = true;
	for (int i = 0; i < db.tags.size(); i++)
	{
		if (db.tags.at(i).ID == data.ID)
		{
			db.tags[i] = data;
			foo = false;
			break;
		}
	}
	if (foo)
	{
		db.tags.append(data);
		addTagIntoAllFileds(data);
	}
}

void DBManager::hasReview(const dbReview& data)
{
	bool foo = true;
	for (int i = 0; i < db.reviews.size(); i++)
	{
		if (db.reviews.at(i).ID == data.ID)
		{
			db.reviews[i] = data;
			foo = false;
			break;
		}
	}
	if (foo)
	{
		db.reviews.append(data);
		addReviewIntoAllFileds(data);
	}
}

/*void DBManager::allReaded()
{
	if (!isTesting)
	{
		if (stackedWidget)
			stackedWidget->setEnabled(true);
	}
	else
		testReadyFlag = ENT::Database; // ?
}*/

///// CREATE

void DBManager::tagCreated(const long long& id, const bool& res)
{
	const QPointer<QWidget> baseWidget = w.at(ENT::Tag).baseWidget;
	if (baseWidget)
		baseWidget->setEnabled(true);
	if (res)
		showAlert("Тег добавлен!");
	else
	{
		if (!removeValue<dbTag>(db.tags, id))
			showAlert("Не удалось удалить временный тег!");
		showAlert("Не удалось создать тег!");
	}
	taskFinished(ENT::Tag, TASK_TYPE::Create, id);
}


void DBManager::reviewCreated(const long long& id, const bool& res)
{
	const QPointer<QWidget> baseWidget = w.at(ENT::Review).baseWidget;
	if (baseWidget)
		baseWidget->setEnabled(true);
	if (res)
		showAlert("Обзор добавлен!");
	else
	{
		if (!removeValue<dbReview>(db.reviews, id))
			showAlert("Не удалось удалить временный обзор!");
		showAlert("Не удалось создать обзор!");
	}
	taskFinished(ENT::Review, TASK_TYPE::Create, id);
}

void DBManager::userCreated(const long long& id, const bool& res)
{
	const QPointer<QWidget> baseWidget = w.at(ENT::User).baseWidget;
	if (baseWidget)
		baseWidget->setEnabled(true);
	if (res)
		showAlert("Пользователь добавлен!");
	else
	{
		if (!removeValue<dbUser>(db.users, id))
			showAlert("Не удалось удалить временного пользователя!");
		showAlert("Не удалось создать пользователя!");
	}
	taskFinished(ENT::User, TASK_TYPE::Create, id);
}

void DBManager::eventCreated(const long long& id, const bool& res)
{
	const QPointer<QWidget> baseWidget = w.at(ENT::Event).baseWidget;
	if (baseWidget)
		baseWidget->setEnabled(false);
	if (res)
		showAlert("Событие добавлено!");
	else
	{
		if (!removeValue<dbEvent>(db.events, id))
			showAlert("Не удалось удалить временное событие!");
		showAlert("Не удалось создать событие!");
	}
	taskFinished(ENT::Event, TASK_TYPE::Create, id);
}

void DBManager::pSiteCreated(const long long& id, const bool& res)
{
	const QPointer<QWidget> baseWidget = w.at(ENT::PSite).baseWidget;
	if (baseWidget)
		baseWidget->setEnabled(false);
	if (res)
		showAlert("Партнерский сайт добавлен!");
	else
	{
		if (!removeValue<dbPartnerSite>(db.partnerSites, id))
			showAlert("Не удалось удалить временный партнерский сайт!");
		showAlert("Не удалось создать партнерский сайт!");
	}
	taskFinished(ENT::PSite, TASK_TYPE::Create, id);
}

void DBManager::mediaCreated(const long long& id, const bool& res)
{
	const QPointer<QWidget> baseWidget = w.at(ENT::Media).baseWidget;
	if (baseWidget)
		baseWidget->setEnabled(false);
	if (res)
		showAlert("Медиа добавлено!");
	else
	{
		if (!removeValue<dbMedia>(db.medias, id))
			showAlert("Не удалось удалить временное медиа!");
		showAlert("Не удалось создать медиа!");
	}
	taskFinished(ENT::Media, TASK_TYPE::Create, id);
}

void DBManager::placeCreated(const long long& id, const bool& res)
{
	const QPointer<QWidget> baseWidget = w.at(ENT::Place).baseWidget;
	if (baseWidget)
		baseWidget->setEnabled(true);
	if (res)
		showAlert("Место добавлено!");
	else
	{
		if (!removeValue<dbPlace>(db.places, id))
			showAlert("Не удалось удалить временное место!");
		showAlert("Не удалось добавить место!");
	}
	taskFinished(ENT::Place, TASK_TYPE::Create, id);
}

///// READ

void DBManager::tagReaded(const long long& id, const bool& res)
{
	taskFinished(ENT::Tag, TASK_TYPE::Read, id);
}

void DBManager::userReaded(const long long& id, const bool& res)
{
	taskFinished(ENT::User, TASK_TYPE::Read, id);
}

void DBManager::eventReaded(const long long& id, const bool& res)
{
	taskFinished(ENT::Event, TASK_TYPE::Read, id);
}

void DBManager::pSiteReaded(const long long& id, const bool& res)
{
	taskFinished(ENT::PSite, TASK_TYPE::Read, id);
}

void DBManager::reviewReaded(const long long& id, const bool& res)
{
	taskFinished(ENT::Review, TASK_TYPE::Read, id);
}

void DBManager::placeReaded(const long long& id, const bool& res)
{
	taskFinished(ENT::Place, TASK_TYPE::Read, id);
}

void DBManager::mediaReaded(const long long& id, const bool& res)
{
	taskFinished(ENT::Media, TASK_TYPE::Read, id);
}

///// UPDATE

void DBManager::tagUpdated(const long long& id, const bool& res)
{
	taskFinished(ENT::Tag, TASK_TYPE::Update, id);
}

void DBManager::userUpdated(const long long& id, const bool& res)
{
	taskFinished(ENT::Tag, TASK_TYPE::Update, id);
}

void DBManager::eventUpdated(const long long& id, const bool& res)
{
	taskFinished(ENT::Tag, TASK_TYPE::Update, id);
}

void DBManager::pSiteUpdated(const long long& id, const bool& res)
{
	taskFinished(ENT::Tag, TASK_TYPE::Update, id);
}

void DBManager::reviewUpdated(const long long& id, const bool& res)
{
	taskFinished(ENT::Tag, TASK_TYPE::Update, id);
}

void DBManager::mediaUpdated(const long long& id, const bool& res)
{
	taskFinished(ENT::Tag, TASK_TYPE::Update, id);
}

void DBManager::placeUpdated(const long long& id, const bool& res)
{
	taskFinished(ENT::Tag, TASK_TYPE::Update, id);
}

///// DELETE

void DBManager::tagDeleted(const long long& id, const bool& res)
{
	taskFinished(ENT::Tag, TASK_TYPE::Delete, id);
}

void DBManager::userDeleted(const long long& id, const bool& res)
{
	taskFinished(ENT::User, TASK_TYPE::Delete, id);
}

void DBManager::eventDeleted(const long long& id, const bool& res)
{
	taskFinished(ENT::Event, TASK_TYPE::Delete, id);
}

void DBManager::pSiteDeleted(const long long& id, const bool& res)
{
	taskFinished(ENT::PSite, TASK_TYPE::Delete, id);
}

void DBManager::reviewDeleted(const long long& id, const bool& res)
{
	taskFinished(ENT::Review, TASK_TYPE::Delete, id);
}

void DBManager::mediaDeleted(const long long& id, const bool& res)
{
	taskFinished(ENT::Media, TASK_TYPE::Delete, id);
}

void DBManager::placeDeleted(const long long& id, const bool& res)
{
	taskFinished(ENT::Place, TASK_TYPE::Delete, id);
}

////////////////////////////////////////////////////////////////
//				THE END
////////////////////////////////////////////////////////////////

QString DBManager::hash(const QString& in)
{
	QString res = QString(QCryptographicHash::hash(in.toUtf8(), QCryptographicHash::Algorithm::Sha3_512).toBase64());
	return res;
}

/*QVector<long long> DBManager::getUsersIdByName(const QStringList& names)
{
	QVector<long long> res;
	for (const dbUser& u : db.users)
		if (names.contains(u.Name))
			res.append(u.ID);
	return res;
}*/

void DBManager::haveAnError(const QString& s)
{
	if (logField)
		logField->appendPlainText(s);
	qDebug() << s;
}

void DBManager::testDatabase()
{
	// TODO
}
/*void DBManager::waitForAllReaded()
{
	for (;;)
	{
		QApplication::processEvents();
		if (testReadyFlag >= ENT::Database)
			break;
		QThread::msleep(100);
	}
}

void DBManager::validateTestData()
{
	if (testDb.events.size() == 1)
	{
		if (!(testDb.events.at(0) == td.event))
			log("Event data mismath!");
	}
	else
		log("Event count mismatch!");

	if (testDb.places.size() == 1)
	{
		if (!(testDb.places.at(0) == td.place))
			log("Event data mismath!");
	}
	else
		log("Event count mismatch!");

	if (testDb.medias.size() == 1)
	{
		if (!(testDb.medias.at(0) == td.media))
			log("Event data mismath!");
	}
	else
		log("Event count mismatch!");

	if (testDb.users.size() == 1)
	{
		if (!(testDb.users.at(0) == td.user))
			log("Event data mismath!");
	}
	else
		log("Event count mismatch!");

	if (testDb.partnerSites.size() == 1)
	{
		if (!(testDb.partnerSites.at(0) == td.psite))
			log("Event data mismath!");
	}
	else
		log("Event count mismatch!");

	if (testDb.tags.size() == 1)
	{
		if (!(testDb.tags.at(0) == td.tag))
			log("Event data mismath!");
	}
	else
		log("Event count mismatch!");

	if (testDb.reviews.size() == 1)
	{
		if (!(testDb.reviews.at(0) == td.review))
			log("Event data mismath!");
	}
	else
		log("Event count mismatch!");
}

void DBManager::readTestDataFromDB()
{
	emit readEvent(td.review.ID);
	emit readPlace(td.place.ID);
	emit readMedia(td.media.ID);
	emit readUser(td.user.ID);
	emit readPSite(td.psite.ID);
	emit readTag(td.tag.ID);
	emit readReview(td.review.ID);
}

void DBManager::testDatabase()
{
	////// Section #1 - test SQL

	isTesting = true;

	// добавляем к id 1
	// проверяем изменение
	// удаляем все
	// проверяем изменение

	// сначала заносим все тестовые данные
	//fillTestData(td);

	// добавляем все сущности (внутри
	testReadyFlag = 0;
	clearTestDatabase();
	createErrors.reserve(ENT::Database);
	testCreateReview();
	testCreatePSite();
	testCreatePlace();
	testCreateMedia();
	testCreateTag();
	testCreateEvent();
	waitForAllReaded();

	// читаем добавленное
	testReadyFlag = 0;
	readTestDataFromDB();
	waitForAllReaded();

	// проверяем прочитанное
	validateTestData();

TODO:
	//// test update
	QStringList updateErrors;
	void testUpdateReview();
	void testUpdatePSite();
	void testUpdatePlace();
	void testUpdateMedia();
	void testUpdateTag();
	void testUpdateEvent();

	//// test delete
	QStringList deleteErrors;
	void testDeleteReview();
	void testDeletePSite();
	void testDeletePlace();
	void testDeleteMedia();
	void testDeleteTag();
	void testDeleteEvent();

	//// read existing database

}

void DBManager::clearTestDatabase()
{
	testEvents.clear();
	testPlaces.clear();
	testMedias.clear();
	testUsers.clear();
	testPartnerSites.clear();
	testTags.clear();
	testReviews.clear();
}
*/