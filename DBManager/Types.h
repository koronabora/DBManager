#pragma once
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QVector>

static const QString DATE_PERIOD_DIV = "-";
static const QString DATE_PERIOD_PARSE_FORMAT = "MM/ddhh:mm";
static const QString DATE_PERIOD_FORMAT = "MM/dd hh:mm:ss";
static const QString DATE_PERIOD_PERIODIC_FLAG = "*";

struct dbEvent
{
	long long ID;// = `gorm:"primary_key" json:"id"`
	QString Name;// `json:"name"`

	QDateTime CreatedAt; // `json:"created"`
	QDateTime UpdatedAt;// time.Time `json:"updated"`
	QDateTime DeletedAt;// *time.Time

	QString ShDescr;//    string        `json:"shdescr"`
	QString FullDescr;//  string        `json:"fulldescr"`
	QString Routing;// string        `json:"route"`
	QVector<long long> Places;//      pq.Int64Array `gorm:"type:bigint[]" json:"places"`
	QVector<long long> Users;//   pq.Int64Array `gorm:"type:bigint[]" json:"users"`
	QVector<long long> Tags;//    pq.Int64Array `gorm:"type:bigint[]" json:"tags"`
	long long Rate;//int64         `json:"rate"`
	QVector<long long> Reviews;//    pq.Int64Array `gorm:"type:bigint[]" json:"reviews"`
	QVector<long long> PartnerSite;// pq.Int64Array `gorm:"type:bigint[]" json:"psite"`
	QVector<long long> Media;// pq.Int64Array `gorm:"type:bigint[]" json:"media"`
	// string list of periods for year (MM/dd hh:mm:ss). If last string is "*" - subject is periodical
	// like:
	// 12/31 22:00:00 - start of period
	// 01/06 23:59:59 - end of the period
	// *
	// or
	// 03/08 00:00:00
	// 03/08 23:59:59
	// *
	QStringList Timetable;//[]string      `gorm:"type:text[]" json:"timetable"`
	QString Extra1;//string        `json:"ex1"`
	QString Extra2;//   string        `json:"ex2"`
	bool isValid()
	{
		if (ID < 0 || Name.isEmpty())
			return false;
		return true;
	};
};

struct dbTag
{
	long long ID;//   int64 `gorm:"primary_key" json:"id"`
	QDateTime CreatedAt; // `json:"created"`
	QDateTime UpdatedAt;// time.Time `json:"updated"`
	QDateTime DeletedAt;// *time.Time
	QString Name;// string `json:"name"`
	bool isValid()
	{
		if (ID < 0 || Name.isEmpty())
			return false;
		return true;
	};
};

struct dbUser
{
	long long  ID;//int64    `gorm:"primary_key" json:"id"`
	QDateTime CreatedAt;//time.Time `json:"created"`
	QDateTime UpdatedAt;//time.Time `json:"updated"`
	QDateTime DeletedAt;// *time.Time
	QString Name;// string   `json:"name"`
	QString Surname;//string   `json:"surname"`
	QStringList Contacts;//[]string `gorm:"type:text[]" json:"contacts"`
	QString PassHash;//  string   `json:"passhash"`
	QString Login;//   string   `json:"login"`
	QString Userpic;//   string   `json:"usrpic"`
	bool isValid()
	{
		if (ID < 0 || Login.isEmpty() || PassHash.isEmpty())
			return false;
		return true;
	};
};

struct dbPartnerSite
{
	long long ID;//      int64    `gorm:"primary_key" json:"id"`
	QDateTime CreatedAt;// time.Time `json:"created"`
	QDateTime UpdatedAt;//time.Time `json:"updated"`
	QDateTime DeletedAt;//*time.Time
	QString Ref;//string `json:"ref"`
	QString Def;//      string `json:"def"`
	bool isValid()
	{
		if (ID < 0 || Ref.isEmpty())
			return false;
		return true;
	};
};

struct dbReview
{
	long long ID;//int64    `gorm:"primary_key" json:"id"`
	QDateTime CreatedAt;// time.Time `json:"created"`
	QDateTime UpdatedAt;// time.Time `json:"updated"`
	QDateTime DeletedAt;//*time.Time
	QString Text;// string        `json:"text"`
	QString Rate;//    int64         `json:"rate"`
	QVector<long long> Users;//   pq.Int64Array `gorm:"type:bigint[]" json:"users"`
	QDateTime AddTime;//  string        `json:"time"`
	bool isValid()
	{
		if (ID < 0 || Text.isEmpty())
			return false;
		return true;
	};
};

struct dbPlace
{
	long long ID;//  int64    `gorm:"primary_key" json:"id"`
	QDateTime CreatedAt;// time.Time `json:"created"`
	QDateTime UpdatedAt;//time.Time `json:"updated"`
	QDateTime DeletedAt;// *time.Time
	QString Name;// string        `json:"name"`
	QString Descr;//    string        `json:"descr"`
	qreal CoordX;// float64       `json:"X"`
	qreal CoordY;//  float64       `json:"Y"`
	QString Address;//  string        `json:"address"`
	QVector<long long> Media;//     pq.Int64Array `gorm:"type:bigint[]" json:"media"`
	bool isValid()
	{
		if (ID < 0 || Name.isEmpty())
			return false;
		if (CoordX < -90.0 || CoordX>90.0)
			return false;
		if (CoordY < -180.0 || CoordY > 180.0)
			return false;
		return true;
	};
};

struct dbMedia
{
	long long ID;// int64    `gorm:"primary_key" json:"id"`
	QDateTime CreatedAt;//time.Time `json:"created"`
	QDateTime UpdatedAt;//time.Time `json:"updated"`
	QDateTime DeletedAt;// *time.Time
	QString Name;//   string `json:"name"`

	long long Rate;//  int64          `json:"rate"`
	//QVector<long long> Events;//pq.Int64Array  `gorm:"type:bigint[]" json:"events"`
	QStringList References;// pq.StringArray `gorm:"type:text[]" json:"refs"`

	QString Descr;//string `json:"descr"`
	bool isValid()
	{ 
		if (ID < 0 || Name.isEmpty())
			return false;
		return true;
	};
};

struct testData
{
	dbEvent event;
	dbPlace place;
	dbMedia media;
	dbUser user;
	dbPartnerSite psite;
	dbTag tag;
	dbReview review;
};

static bool operator==(const dbEvent& a1, const dbEvent& a2)
{
	return a1.ID == a2.ID &&
		a1.Name == a2.Name &&
		a1.CreatedAt == a2.CreatedAt &&
		a1.UpdatedAt == a2.UpdatedAt &&
		a1.DeletedAt == a2.DeletedAt &&
		a1.ShDescr == a2.ShDescr &&
		a1.FullDescr == a2.FullDescr &&
		a1.Routing == a2.Routing &&
		a1.Places == a2.Places &&
		a1.Users == a2.Users &&
		a1.Tags == a2.Tags &&
		a1.Rate == a2.Rate &&
		a1.Reviews == a2.Reviews &&
		a1.PartnerSite == a2.PartnerSite &&
		a1.Media == a2.Media &&
		a1.Timetable == a2.Timetable &&
		a1.Extra1 == a2.Extra1 &&
		a1.Extra2 == a2.Extra2;
}

static bool operator==(const dbTag& a1, const dbTag& a2)
{
	return a1.ID == a2.ID &&
		a1.CreatedAt == a2.CreatedAt &&
		a1.UpdatedAt == a2.UpdatedAt &&
		a1.DeletedAt == a2.DeletedAt &&
		a1.Name == a2.Name;
};

static bool operator==(const dbUser& a1, const dbUser& a2)
{
	return a1.ID == a2.ID &&
		a1.CreatedAt == a2.CreatedAt &&
		a1.UpdatedAt == a2.UpdatedAt &&
		a1.DeletedAt == a2.DeletedAt &&
		a1.Name == a2.Name &&
		a1.Surname == a2.Surname &&
		a1.Contacts == a2.Contacts &&
		a1.PassHash == a2.PassHash &&
		a1.Login == a2.Login &&
		a1.Userpic == a2.Userpic;
};

static bool operator==(const dbPartnerSite& a1, const dbPartnerSite& a2)
{
	return a1.ID == a2.ID &&
		a1.CreatedAt == a2.CreatedAt &&
		a1.UpdatedAt == a2.UpdatedAt &&
		a1.DeletedAt == a2.DeletedAt &&
		a1.Ref == a2.Ref &&
		a1.Def == a2.Def;
};

static bool operator==(const dbReview& a1, const dbReview& a2)
{
	return a1.ID == a2.ID &&
		a1.CreatedAt == a2.CreatedAt &&
		a1.UpdatedAt == a2.UpdatedAt &&
		a1.DeletedAt == a2.DeletedAt &&
		a1.Text == a2.Text &&
		a1.Rate == a2.Rate &&
		a1.Users == a2.Users &&
		a1.AddTime == a2.AddTime;
};

static bool operator==(const dbPlace& a1, const dbPlace& a2)
{
	return a1.ID == a2.ID &&
		a1.CreatedAt == a2.CreatedAt &&
		a1.UpdatedAt == a2.UpdatedAt &&
		a1.DeletedAt == a2.DeletedAt &&
		a1.Name == a2.Name &&
		a1.Descr == a2.Descr &&
		a1.CoordX == a2.CoordX &&
		a1.CoordY == a2.CoordY &&
		a1.Address == a2.Address &&
		a1.Media == a2.Media;
};

static bool operator==(const dbMedia& a1, const dbMedia& a2)
{
	return a1.ID == a2.ID &&
		a1.CreatedAt == a2.CreatedAt &&
		a1.UpdatedAt == a2.UpdatedAt &&
		a1.DeletedAt == a2.DeletedAt &&
		a1.Name == a2.Name &&
		a1.Rate == a2.Rate &&
		a1.References == a2.References &&
		a1.Descr == a2.Descr;
};

struct DbStruct
{
	QVector<dbEvent> events;
	QVector<dbPlace> places;
	QVector<dbMedia> medias;
	QVector<dbUser> users;
	QVector<dbPartnerSite> partnerSites;
	QVector<dbTag> tags;
	QVector<dbReview> reviews;
};

enum ENT
{
	Tag,
	User,
	Review,
	Event,
	PSite,
	Media,
	Place,
	Database // has to be last
};

enum TASK_TYPE
{
	Create,
	Read,
	Update,
	Delete,
	Test
};

struct Task
{
	ENT obj = ENT::Database;
	TASK_TYPE type = TASK_TYPE::Test;
	long long objId = 0;
	Task(ENT _obj, TASK_TYPE _type, long long _objId)
	{
		obj = _obj;
		type = _type;
		objId = _objId;
	};
	Task() {};
	
	static QString objName(const ENT& _obj)
	{
		QString res;
		switch (_obj)
		{
		case ENT::Database:
			res += "Database";
			break;
		case ENT::Event:
			res += "Event";
			break;
		case ENT::Media:
			res += "Media";
			break;
		case ENT::Place:
			res += "Place";
			break;
		case ENT::PSite:
			res += "PSite";
			break;
		case ENT::Review:
			res += "Review";
			break;
		case ENT::Tag:
			res += "Tag";
			break;
		case ENT::User:
			res += "User";
			break;
		};
		return res;
	};
	static QString typeName(const TASK_TYPE& _type)
	{
		QString res;
		switch (_type)
		{
		case TASK_TYPE::Create:
			res += "Create";
			break;
		case TASK_TYPE::Delete:
			res += "Delete";
			break;
		case TASK_TYPE::Read:
			res += "Read";
			break;
		case TASK_TYPE::Test:
			res += "Test";
			break;
		case TASK_TYPE::Update:
			res += "Update";
			break;
		};
		return res;
	};
	QString toString() const
	{
		QString res = "Task -> ";
		res += objName(obj);
		res += " | ";
		res += typeName(type);
		res += " | ";
		res += QString::number(objId);
		return res;
	};
};