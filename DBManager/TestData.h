#pragma once

#include "Types.h"

#define TEST_ID 999999999

static void fillTestData(testData& td)
{
	// td.event 
	td.event.CreatedAt = QDateTime::currentDateTime();
	td.event.Extra1 = "extra1";
	td.event.Extra2 = "extra2";
	td.event.FullDescr = "full descr";
	td.event.ID = TEST_ID;
	td.event.Media = { TEST_ID };
	td.event.Name = "Name";
	td.event.PartnerSite = { TEST_ID };
	td.event.Places = { TEST_ID };
	td.event.Rate = 10;
	td.event.Reviews = { TEST_ID };
	td.event.Routing = "No matters!";
	td.event.ShDescr = "Test event";
	td.event.Tags = { TEST_ID };
	td.event.Timetable = QStringList({ "00 21 13 02 * */2" }); // каждые 2 года 13 февраля в 21:00
	td.event.UpdatedAt = td.event.CreatedAt;
	td.event.Users = { TEST_ID };

	// td.media
	td.media.CreatedAt = QDateTime::currentDateTime();
	//td.media.DeletedAt = ;
	td.media.Descr = "Description";
	td.media.ID = TEST_ID;
	td.media.Name = "Name";
	td.media.Rate = 10;
	td.media.References = QStringList("https://imgprx.livejournal.net/bc34dc8ad0be8d855897eda9dbeb6a5ae0816e5d/MvKOiGM9cyRKbNV9VOvfNb-mZ9meTTmjgSrXmiKMGDCqhWyRveyc2JsMwGm5QVkkCsbKg83hdaZAwNntt_Nl1_PGq4-MeYjgOrsTKpr36-M");
	td.media.UpdatedAt =QDateTime::currentDateTime() ;

	// td.place
	td.place.Address = "Sample Address";
	td.place.CoordX = 59.950181;
	td.place.CoordY = 30.317481;
	td.place.CreatedAt = QDateTime::currentDateTime();
	//td.place.DeletedAt = ;
	td.place.Descr = "Description";
	td.place.ID = TEST_ID;
	td.place.Media = { TEST_ID };
	td.place.Name = "Name";
	td.place.UpdatedAt = QDateTime::currentDateTime();

	//td.psite
	td.psite.CreatedAt = QDateTime::currentDateTime();
	td.psite.Def = "Partner definition";
	//td.psite.DeletedAt = ;
	td.psite.ID = TEST_ID;
	td.psite.Ref = "http://google.com";
	td.psite.UpdatedAt = QDateTime::currentDateTime();

	//td.review 
	td.review.AddTime = QDateTime::currentDateTime();
	td.review.CreatedAt = QDateTime::currentDateTime();
	//td.review.DeletedAt = ;
	td.review.ID = TEST_ID;
	td.review.Rate = 10;
	td.review.Text = "Bset event I ever seen!";
	td.review.UpdatedAt = QDateTime::currentDateTime();
	td.review.Users = { TEST_ID };
	
	//td.tag
	td.tag.CreatedAt = QDateTime::currentDateTime();
	//td.tag.DeletedAt = ;
	td.tag.ID = TEST_ID;
	td.tag.Name = "Name";
	td.tag.UpdatedAt = QDateTime::currentDateTime();

	//td.user 
	td.user.Contacts = QStringList({"aleksander.boldyrev@gmail.com"});
	td.user.CreatedAt = QDateTime::currentDateTime();
	//td.user.DeletedAt = ;
	td.user.ID = TEST_ID;
	td.user.Login = "admin";
	td.user.Name = "Name";
	td.user.PassHash = "21f9ff061b755faaa06d71434f31330582901810871c228a4d67f9e52f2adf82ea6b445bb4c98d49da68fb140717911e4fc5e1c49ec0becf0aadec0f7517f8bc";
	td.user.Surname = "Surname";
	td.user.UpdatedAt = QDateTime::currentDateTime();
	td.user.Userpic = "https://sun9-41.userapi.com/c205828/v205828116/f84f/eQLTRuiXoJ0.jpg";
}
