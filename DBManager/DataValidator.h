#pragma once

#include <QObject>

#include "DBHandler.h"

class DataValidator : public QObject
{
	Q_OBJECT

private:

public:
	DataValidator();
	~DataValidator();

	void run();

public slots:
	void validateDb();
	void validateDbHandler();

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
	void workFinished();
	
	void dbValidated(const bool& res);
	void dbbHandlerValidated(const bool& res);

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