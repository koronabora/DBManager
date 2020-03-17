#include "DataValidator.h"

DataValidator::DataValidator()
{
}

DataValidator::~DataValidator()
{
	emit workFinished();
}

void DataValidator::run()
{}

void DataValidator::validateDb()
{}

void DataValidator::validateDbHandler()
{}


void DataValidator::hasEvent(const dbEvent& data)
{}

void DataValidator::hasPlace(const dbPlace& data)
{}

void DataValidator::hasMedia(const dbMedia& data)
{}

void DataValidator::hasUser(const dbUser& data)
{}

void DataValidator::hasPSite(const dbPartnerSite& data)
{}

void DataValidator::hasTag(dbTag data)
{}

void DataValidator::hasReview(const dbReview& data)
{}

void DataValidator::tagCreated(const long long& id, const bool& res)
{}

void DataValidator::tagReaded(const long long& id, const bool& res)
{}

void DataValidator::tagUpdated(const long long& id, const bool& res)
{}

void DataValidator::tagDeleted(const long long& id, const bool& res)
{}

void DataValidator::userCreated(const long long& id, const bool& res)
{}

void DataValidator::userReaded(const long long& id, const bool& res)
{}

void DataValidator::userUpdated(const long long& id, const bool& res)
{}

void DataValidator::userDeleted(const long long& id, const bool& res)
{}

void DataValidator::eventCreated(const long long& id, const bool& res)
{}

void DataValidator::eventReaded(const long long& id, const bool& res)
{}

void DataValidator::eventUpdated(const long long& id, const bool& res)
{}

void DataValidator::eventDeleted(const long long& id, const bool& res)
{}

void DataValidator::pSiteCreated(const long long& id, const bool& res)
{}

void DataValidator::pSiteReaded(const long long& id, const bool& res)
{}

void DataValidator::pSiteUpdated(const long long& id, const bool& res)
{}

void DataValidator::pSiteDeleted(const long long& id, const bool& res)
{}

void DataValidator::reviewCreated(const long long& id, const bool& res)
{}

void DataValidator::reviewReaded(const long long& id, const bool& res)
{}

void DataValidator::reviewUpdated(const long long& id, const bool& res)
{}

void DataValidator::reviewDeleted(const long long& id, const bool& res)
{}

void DataValidator::mediaCreated(const long long& id, const bool& res)
{}

void DataValidator::mediaReaded(const long long& id, const bool& res)
{}

void DataValidator::mediaUpdated(const long long& id, const bool& res)
{}

void DataValidator::mediaDeleted(const long long& id, const bool& res)
{}

void DataValidator::placeCreated(const long long& id, const bool& res)
{}

void DataValidator::placeReaded(const long long& id, const bool& res)
{}

void DataValidator::placeUpdated(const long long& id, const bool& res)
{}

void DataValidator::placeDeleted(const long long& id, const bool& res)
{}
