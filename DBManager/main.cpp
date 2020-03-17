#include <QtWidgets/QApplication>
#include <QThread>
#include <QSharedPointer>

#include "DBManager.h"
#include "DBHandler.h"
#include "DataValidator.h"

static const int THREAD_WAIT_TIME = 500;

/*
TODO:
	- поставить на VDS gitlab
	- закинуть туда все наши проекты

	- сделать обратную связь от методов рабты с базой в основоном классе
	- сделать валидацию базы
*/

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	qRegisterMetaType<dbTag>("dbTag");
	qRegisterMetaType<dbEvent>("dbEvent");
	qRegisterMetaType<dbUser>("dbUser");
	qRegisterMetaType<dbPartnerSite>("dbPartnerSite");
	qRegisterMetaType<dbReview>("dbReview");
	qRegisterMetaType<dbPlace>("dbPlace");
	qRegisterMetaType<dbMedia>("dbMedia");

	DBManager gui;
	DBHandler* w = new DBHandler();
	DataValidator* dv = new DataValidator();
	
	QThread* th = new QThread();
	w->moveToThread(th);
	QObject::connect(th, &QThread::started, w, &DBHandler::run);
	QObject::connect(w, &DBHandler::workFinished, th, &QThread::terminate);
	//QObject::connect(&th, SIGNAL(finished()), &w, SLOT(deleteLater()));
	//QObject::connect(th, &QThread::finished, th, &QThread::deleteLater);
	th->start();

	QThread* th2 = new QThread();
	dv->moveToThread(th2);
	QObject::connect(th2, &QThread::started, dv, &DataValidator::run);
	QObject::connect(dv,&DataValidator::workFinished, th2, &QThread::terminate);
	//QObject::connect(&th, SIGNAL(finished()), &w, SLOT(deleteLater()));
	//QObject::connect(th2, &QThread::finished, th2, &QThread::deleteLater);
	th2->start();
	
	gui.show();
	gui.run(w, dv);
	const int res = a.exec();
	w->deleteLater();
	dv->deleteLater();
	//th->wait();
	//th->terminate();
	//th->quit();
	th->wait(THREAD_WAIT_TIME);
	th->quit();
	th->deleteLater();
	//th2.quit();
	th2->wait(THREAD_WAIT_TIME);
	th2->quit();
	th2->deleteLater();
	return res;
}
