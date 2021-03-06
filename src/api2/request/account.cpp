#include "../instagramv2_p.h"
#include "../instagramrequestv2.h"
#include <QJsonObject>

void Instagramv2::changeProfilePicture(QFile *photo)
{

}

void Instagramv2::removeProfilePicture()
{
    Q_D(Instagramv2);

    QJsonObject data;
        data.insert("_uuid",        d->m_uuid);
        data.insert("_uid",         d->m_username_id);
        data.insert("_csrftoken",   "Set-Cookie: csrftoken="+d->m_token);

    QString signature = InstagramRequestv2::generateSignature(data);
    InstagramRequestv2 *removeProfilePictureRequest =
        d->request("accounts/remove_profile_picture/",signature.toUtf8());
    QObject::connect(removeProfilePictureRequest,&InstagramRequestv2::replyStringReady,this,&Instagramv2::profilePictureDeleted);
}

void Instagramv2::setPrivateAccount()
{
    Q_D(Instagramv2);

    QJsonObject data;
        data.insert("_uuid",        d->m_uuid);
        data.insert("_uid",         d->m_username_id);
        data.insert("_csrftoken",   "Set-Cookie: csrftoken="+d->m_token);

    QString signature = InstagramRequestv2::generateSignature(data);
    InstagramRequestv2 *setPrivateRequest =
        d->request("accounts/set_private/",signature.toUtf8());
    QObject::connect(setPrivateRequest,&InstagramRequestv2::replyStringReady,this,&Instagramv2::setProfilePrivate);
}

void Instagramv2::setPublicAccount()
{
    Q_D(Instagramv2);

    QJsonObject data;
        data.insert("_uuid",        d->m_uuid);
        data.insert("_uid",         d->m_username_id);
        data.insert("_csrftoken",   "Set-Cookie: csrftoken="+d->m_token);

    QString signature = InstagramRequestv2::generateSignature(data);
    InstagramRequestv2 *setPublicRequest =
        d->request("accounts/set_public/",signature.toUtf8());
    QObject::connect(setPublicRequest,&InstagramRequestv2::replyStringReady,this,&Instagramv2::setProfilePublic);
}

//getProfileData
void Instagramv2::getCurrentUser()
{
    Q_D(Instagramv2);

    QJsonObject data;
        data.insert("_uuid",        d->m_uuid);
        data.insert("_uid",         d->m_username_id);
        data.insert("_csrftoken",   "Set-Cookie: csrftoken="+d->m_token);

    QString signature = InstagramRequestv2::generateSignature(data);
    InstagramRequestv2 *getCurrentUserRequest =
        d->request("accounts/current_user/?edit=true",signature.toUtf8());
    QObject::connect(getCurrentUserRequest,&InstagramRequestv2::replyStringReady,this,&Instagramv2::currentUserDataReady);
}

/**
 * Edit profile.
 *
 * @param QString url
 *   Url - website. "" for nothing
 * @param QString phone
 *   Phone number. "" for nothing
 * @param QString first_name
 *   Name. "" for nothing
 * @param QString email
 *   Email. Required.
 * @param bool gender
 *   Gender. male = true , female = false
 */
void Instagramv2::editProfile(QString url, QString phone, QString first_name, QString biography, QString email, bool gender)
{
    Q_D(Instagramv2);

    getCurrentUser();

    QString gen_string;
    if(gender)
    {
        gen_string = "1";
    }
    else
    {
        gen_string = "0";
    }

    QJsonObject data;
        data.insert("_uuid",        d->m_uuid);
        data.insert("_uid",         d->m_username_id);
        data.insert("_csrftoken",   "Set-Cookie: csrftoken="+d->m_token);
        data.insert("external_url", url);
        data.insert("phone_number", phone);
        data.insert("username",     d->m_username);
        data.insert("first_name",    first_name);
        data.insert("biography",    biography);
        data.insert("email",        email);
        data.insert("gender",       gen_string);

    QString signature = InstagramRequestv2::generateSignature(data);
    InstagramRequestv2 *editProfileRequest =
        d->request("accounts/edit_profile/?edit=true",signature.toUtf8());
    QObject::connect(editProfileRequest,&InstagramRequestv2::replyStringReady,this,&Instagramv2::editDataReady);
}

/*
 * Return json string
 * {
 *   "username":    STRING  Checking username,
 *   "available":   BOOL    Aviable to registration,
 *   "status":      STRING  Status of request,
 *   "error":       STRING  Error string if aviable
 *   }
 */
void Instagramv2::checkUsername(QString username)
{
    Q_D(Instagramv2);

    QJsonObject data;
        data.insert("_uuid",        d->m_uuid);
        data.insert("_csrftoken",   QString("missing"));
        data.insert("username",     username);
        data.insert("_uid",         d->m_username_id);

    QString signature = InstagramRequestv2::generateSignature(data);
    InstagramRequestv2 *checkUsernameRequest =
        d->request("users/check_username/",signature.toUtf8());
    QObject::connect(checkUsernameRequest,&InstagramRequestv2::replyStringReady,this,&Instagramv2::usernameCheckDataReady);
}

/*
 * Return JSON string
 * {
 *  "status": STRING    Status of request,
 *  "errors":{
 *            ARRAY     Array of errors if aviable
 *      "password":[],  STRING  Error message if password wrong if aviable
 *      "email":[],     STRING  Error message if email wrong if aviable
 *      "FIELD_ID":[]   STRING  Error message if FIELD_ID wrong if aviable
 *  },
 *  "account_created",  BOOL Status of creation account
 *  "created_user"      ARRAY Array of new user params
 *  }
 *
 */
void Instagramv2::createAccount(QString username, QString password, QString email)
{
    Q_D(Instagramv2);

    QJsonObject data;
        data.insert("_uuid",               d->m_uuid);
        data.insert("_csrftoken",          QString("missing"));
        data.insert("username",            username);
        data.insert("first_name",          QString(""));
        data.insert("guid",                d->m_uuid);
        data.insert("device_id",           d->m_device_id);
        data.insert("email",               email);
        data.insert("force_sign_up_code",  QString(""));
        data.insert("qs_stamp",            QString(""));
        data.insert("password",            password);

    QString signature = InstagramRequestv2::generateSignature(data);
    InstagramRequestv2 *createAccountRequest =
        d->request("accounts/create/",signature.toUtf8());
    QObject::connect(createAccountRequest,&InstagramRequestv2::replyStringReady,this,&Instagramv2::createAccountDataReady);
}
