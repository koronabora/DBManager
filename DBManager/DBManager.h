#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DBManager.h"
#include <QPointer>
#include <QPushButton>
#include <QDebug>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QVector>
#include <QThread>
#include <QSharedPointer>
#include <QTableWidget>

#include "Types.h"
#include "TestData.h"
#include "DataValidator.h"
#include "ListBox.h"
#include "VectorWrapper.h"
#include <memory> 

// TODO:
// - добавить экранирование символов
// - сделать валидацию связности базы
// - сделать тестирование

struct widgetStruct
{
	QPointer<QPushButton> openButton;
	QPointer<QPushButton> createButton;
	QPointer<QPushButton> goBackButton;
	QPointer<QWidget> baseWidget;
};

class DBManager : public QMainWindow
{
	Q_OBJECT

public:
	DBManager(QWidget *parent = Q_NULLPTR);

	void run(QPointer<DBHandler> dbClass, QPointer<DataValidator> testClass);
private:
	Ui::DBManagerClass ui;

	QVector<widgetStruct> w;

	QPointer<QStackedWidget> stackedWidget;
	QPointer<QWidget> mainPage;
	QPointer<QPlainTextEdit> logField;
	QPointer<QTableWidget> tasksTable;

	void bindAllButtons();
	void log(const QString& t);
	void showAlert(const QString& text);
	QString hash(const QString& in);
	QStringList parseTimeTable(const QStringList& src);

	void testDatabase();
	
	void fetchUser();
	void fetchReview();
	void fetchPSite();
	void fetchPlace();
	void fetchMedia();
	void fetchTag();
	void fetchEvent();

	QPointer<DataValidator> validator;
	QPointer<DBHandler> dbHandler;
	void connectAll();
	void disconnectAll();

	DbStruct db;

	void addUserIntoAllFileds(const dbUser& u);
	void addMediaIntoAllFileds(const dbMedia& m);
	void addPSiteIntoAllFileds(const dbPartnerSite& ps);
	void addPlaceIntoAllFileds(const dbPlace& pl);
	void addReviewIntoAllFileds(const dbReview& r);
	void addTagIntoAllFileds(const dbTag& t);

	VectorWrapper tasks;

	template <typename T>
	long long getLastId(const QVector<T>& data);
	template <typename T>
	bool checkName(const QVector<T>& data, const QString& name);
	template <typename T>
	bool removeValue(QVector<T>& data, const long long& id);

	void taskFinished(const ENT& _obj, const TASK_TYPE& _type, const long long& _objId);
	/*QVector<long long> getUsersIdByName(const QStringList& names);

	void waitForAllReaded();
	void clearTestDatabase();
	void validateTestData();
	void readTestDataFromDB();*/

	// testing methods
	/*std::atomic_int testReadyFlag = 0;
	bool isTesting = false;
	DbStruct testDb;

	testData td;

	QStringList createErrors;
	void testCreateReview();
	void testCreatePSite();
	void testCreatePlace();
	void testCreateMedia();
	void testCreateTag();
	void testCreateEvent();

	QStringList updateErrors;
	void testUpdateReview();
	void testUpdatePSite();
	void testUpdatePlace();
	void testUpdateMedia();
	void testUpdateTag();
	void testUpdateEvent();

	QStringList deleteErrors;
	void testDeleteReview();
	void testDeletePSite();
	void testDeletePlace();
	void testDeleteMedia();
	void testDeleteTag();
	void testDeleteEvent();*/

private slots:
	void openButtonClicked();
	void createButtonClicked();
	void goBackButtonClicked();

	void taskRemoved(const size_t& pos);
	void taskInserted(const Task& data);

public slots:
	
	void haveAnError(const QString& s); // logging

	void hasEvent(const dbEvent& data);
	void hasPlace(const dbPlace& data);
	void hasMedia(const dbMedia& data);
	void hasUser(const dbUser& data);
	void hasPSite(const dbPartnerSite& data);
	void hasTag(dbTag data);
	void hasReview(const dbReview& data);

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

signals:

	void validateDb();
	void validateDbHandler();

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

};
