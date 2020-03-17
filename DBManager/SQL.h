#pragma once

#include <QObject>
#include <QString>

const QString CREATE_TAG = "INSERT INTO public.tags(id, created_at, updated_at, deleted_at, name) VALUES(?, ?, ?, ?, ?); ";
const QString READ_TAG = "SELECT id, created_at, updated_at, deleted_at, name FROM public.tags;";
const QString READ_TAG_BY_ID = "SELECT id, created_at, updated_at, deleted_at, name FROM public.tags WHERE id = ?;";
const QString UPDATE_TAG = "UPDATE public.tags SET updated_at = ?, \"name\" = ? WHERE id = ?; ";
const QString DELETE_TAG = "UPDATE public.tags SET deleted_at = ? WHERE id = ?;";

const QString CREATE_USER = "INSERT INTO public.users(id, created_at, updated_at, deleted_at, name, surname, contacts, pass_hash, login, userpic) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
const QString READ_USER = "SELECT id, created_at, updated_at, deleted_at, \"name\", surname, contacts, pass_hash, login, userpic FROM public.users; ";
const QString READ_USER_BY_ID = "SELECT id, created_at, updated_at, deleted_at, \"name\", surname, contacts, pass_hash, login, userpic FROM public.users WHERE id = ?; ";
const QString UPDATE_USER = "UPDATE public.users SET updated_at = ?, \"name\" = ?, surname = ?, contacts = ? , pass_hash = ?, login = ?, userpic = ? WHERE id = ?; ";
const QString DELETE_USER = "UPDATE public.users SET deleted_at = ? WHERE id = ?;";

const QString CREATE_EVENT = "INSERT INTO public.events(id, name, created_at, updated_at, deleted_at, sh_descr, full_descr, routing, places, users, tags, rate, reviews, partner_site, media, timetable, extra1, extra2) VALUES(? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? ); ";
const QString READ_EVENT = "SELECT id, name, created_at, updated_at, deleted_at, sh_descr, full_descr, routing, places, users, tags, rate, reviews, partner_site, media, timetable, extra1, extra2 FROM public.events; ";
const QString READ_EVENT_BY_ID = "SELECT id, name, created_at, updated_at, deleted_at, sh_descr, full_descr, routing, places, users, tags, rate, reviews, partner_site, media, timetable, extra1, extra2 FROM public.events WHERE id = ?; ";
const QString UPDATE_EVENT = "UPDATE public.events SET \"name\" = ?, updated_at = ?, sh_descr = ?, full_descr = ?, routing = ?, places = ? , users = ? , tags = ? , rate = ?, reviews = ? , partner_site = ? , media = ? , timetable = ? , extra1 = ?, extra2 = ? WHERE id = ?;";
const QString DELETE_EVENT = "UPDATE public.events SET deleted_at = ? WHERE id = ?;";

const QString CREATE_PSITE = "INSERT INTO public.partner_sites(id, created_at, updated_at, deleted_at, ref, def) VALUES (?, ?, ?, ?, ?, ?);";
const QString READ_PSITE = "SELECT id, created_at, updated_at, deleted_at, ref, def FROM public.partner_sites;";
const QString READ_PSITE_BY_ID = "SELECT id, created_at, updated_at, deleted_at, ref, def FROM public.partner_sites WHERE id = ?;";
const QString UPDATE_PSITE = "UPDATE public.partner_sites SET updated_at = ?, \"ref\" = ?, def = ? WHERE id = ?; ";
const QString DELETE_PSITE = "UPDATE public.partner_sites SET deleted_at = ? WHERE id = ?;";

const QString CREATE_REVIEW = "INSERT INTO public.reviews(id, created_at, updated_at, deleted_at, text, rate, users, add_time) VALUES(? , ? , ? , ? , ? , ? , ? , ? ); ";
const QString READ_REVIEW = "SELECT id, created_at, updated_at, deleted_at, text, rate, users, add_time FROM public.reviews;";
const QString READ_REVIEW_BY_ID = "SELECT id, created_at, updated_at, deleted_at, text, rate, users, add_time FROM public.reviews WHERE id = ?;";
const QString UPDATE_REVIEW = "UPDATE public.reviews SET updated_at = ?, \"text\" = ?, rate = ?, users = ? , add_time = ? WHERE id = ?; ";
const QString DELETE_REVIEW = "UPDATE public.reviews SET deleted_at = ? WHERE id = ?;";

const QString CREATE_MEDIA = "INSERT INTO public.media(id, created_at, updated_at, deleted_at, name, rate, \"references\", descr) VALUES(? , ? , ? , ? , ? , ? , ? , ?); ";
const QString READ_MEDIA = "SELECT id, created_at, updated_at, deleted_at, name, rate, \"references\", descr FROM public.media;";
const QString READ_MEDIA_BY_ID = "SELECT id, created_at, updated_at, deleted_at, name, rate, \"references\", descr FROM public.media WHERE id = ?;";
const QString UPDATE_MEDIA = "UPDATE public.media SET updated_at = ?, \"name\" = ?, rate = ?, events = ? , \"references\" = ? , descr = ? WHERE id = ?; ";
const QString DELETE_MEDIA = "UPDATE public.media SET deleted_at = ? WHERE id = ?;";

const QString CREATE_PLACE = "INSERT INTO public.places(id, created_at, updated_at, deleted_at, name, descr, coord_x, coord_y, address, media) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
const QString READ_PLACE = "SELECT id, created_at, updated_at, deleted_at, name, descr, coord_x, coord_y, address, media FROM public.places;";
const QString READ_PLACE_BY_ID = "SELECT id, created_at, updated_at, deleted_at, name, descr, coord_x, coord_y, address, media FROM public.places WHERE id = ?;";
const QString UPDATE_PLACE = "UPDATE public.places SET updated_at = ?, \"name\" = ?, descr = ?, coord_x = ?, coord_y = ?, address = ?, media = ? WHERE id = ?; ";
const QString DELETE_PLACE = "UPDATE public.places SET deleted_at = ? WHERE id = ?;";

const QString DB_PLUGIN = "QPSQL";
const QString DB_HOST   = "127.0.0.1";
const int	  DB_PORT   = 33333;
const QString DB_BASE   = "site_db";
const QString DB_USER   = "site";
const QString DB_PASS   = "hdh98h1on22";
