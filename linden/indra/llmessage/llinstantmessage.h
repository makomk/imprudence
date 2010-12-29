/** 
 * @file llinstantmessage.h
 * @brief Constants and declarations used by instant messages. 
 *
 * $LicenseInfo:firstyear=2002&license=viewergpl$
 * 
 * Copyright (c) 2002-2009, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlifegrid.net/programs/open_source/licensing/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at
 * http://secondlifegrid.net/programs/open_source/licensing/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 * $/LicenseInfo$
 */

#ifndef LL_LLINSTANTMESSAGE_H
#define LL_LLINSTANTMESSAGE_H

#include "llhost.h"
#include "lluuid.h"
#include "llsd.h"
#include "llpointer.h"
#include "llrefcount.h"
#include "v3math.h"

class LLMessageSystem;

// The ImprovedInstantMessage only supports 8 bits in the "Dialog"
// field, so don't go past the byte boundary
enum EInstantMessage
{
	// default. ID is meaningless, nothing in the binary bucket.
	IM_NOTHING_SPECIAL = 0,

	// pops a messagebox with a single OK button
	IM_MESSAGEBOX = 1,

	// pops a countdown messagebox with a single OK button
	// IM_MESSAGEBOX_COUNTDOWN = 2,

	// You've been invited to join a group.
	// ID is the group id.

	// The binary bucket contains a null terminated string
	// representation of the officer/member status and join cost for
	// the invitee. (bug # 7672) The format is 1 byte for
	// officer/member (O for officer, M for member), and as many bytes
	// as necessary for cost.
	IM_GROUP_INVITATION = 3,

	// Inventory offer.
	// ID is the transaction id
	// Binary bucket is a list of inventory uuid and type. 
	IM_INVENTORY_OFFERED = 4,
	IM_INVENTORY_ACCEPTED = 5,
	IM_INVENTORY_DECLINED = 6,

	// Group vote
	// Name is name of person who called vote.
	// ID is vote ID used for internal tracking
	IM_GROUP_VOTE = 7,

	// Group message
	// This means that the message is meant for everyone in the
	// agent's group. This will result in a database query to find all
	// participants and start an im session.
	IM_GROUP_MESSAGE_DEPRECATED = 8,

	// Task inventory offer.
	// ID is the transaction id
	// Binary bucket is a (mostly) complete packed inventory item
	IM_TASK_INVENTORY_OFFERED = 9,
	IM_TASK_INVENTORY_ACCEPTED = 10,
	IM_TASK_INVENTORY_DECLINED = 11,

	// Copied as pending, type LL_NOTHING_SPECIAL, for new users
	// used by offline tools
	IM_NEW_USER_DEFAULT = 12,

	//
	// session based messaging - the way that people usually actually
	// communicate with each other.
	//

	// Invite users to a session.
	IM_SESSION_INVITE = 13,

	IM_SESSION_P2P_INVITE = 14,

	// start a session with your gruop
	IM_SESSION_GROUP_START = 15,

	// start a session without a calling card (finder or objects)
	IM_SESSION_CONFERENCE_START = 16,

	// send a message to a session.
	IM_SESSION_SEND = 17,

	// leave a session
	IM_SESSION_LEAVE = 18,

	// an instant message from an object - for differentiation on the
	// viewer, since you can't IM an object yet.
	IM_FROM_TASK = 19,

	// sent an IM to a busy user, this is the auto response
	IM_BUSY_AUTO_RESPONSE = 20,

	// Shows the message in the console and chat history
	IM_CONSOLE_AND_CHAT_HISTORY = 21,

	// IM Types used for luring your friends
	IM_LURE_USER = 22,
	IM_LURE_ACCEPTED = 23,
	IM_LURE_DECLINED = 24,
	IM_GODLIKE_LURE_USER = 25,
	IM_YET_TO_BE_USED = 26,

	// IM that notifie of a new group election.
	// Name is name of person who called vote.
	// ID is election ID used for internal tracking
	IM_GROUP_ELECTION_DEPRECATED = 27,

	// IM to tell the user to go to an URL. Put a text message in the
	// message field, and put the url with a trailing \0 in the binary
	// bucket.
	IM_GOTO_URL = 28,

	// a message generated by a script which we don't want to
	// be sent through e-mail.  Similar to IM_FROM_TASK, but
	// it is shown as an alert on the viewer.
	IM_FROM_TASK_AS_ALERT = 31,

	// IM from group officer to all group members.
	IM_GROUP_NOTICE = 32,
	IM_GROUP_NOTICE_INVENTORY_ACCEPTED = 33,
	IM_GROUP_NOTICE_INVENTORY_DECLINED = 34,

	IM_GROUP_INVITATION_ACCEPT = 35,
	IM_GROUP_INVITATION_DECLINE = 36,

	IM_GROUP_NOTICE_REQUESTED = 37,

	IM_FRIENDSHIP_OFFERED = 38,
	IM_FRIENDSHIP_ACCEPTED = 39,
	IM_FRIENDSHIP_DECLINED_DEPRECATED = 40,

	IM_TYPING_START = 41,
	IM_TYPING_STOP = 42,

	IM_COUNT
};


// Hooks for quickly hacking in experimental admin debug messages 
// without needing to recompile the viewer
// *NOTE: This functionality has been moved to be a string based
// operation so that we don't even have to do a full recompile. This
// enumeration will be phased out soon.
enum EGodlikeRequest
{
	GOD_WANTS_NOTHING,

	// for requesting physics information about an object
	GOD_WANTS_PHYSICS_INFO,
	
	// two unused requests that can be appropriated for debug 
	// purposes (no viewer recompile necessary)
	GOD_WANTS_FOO,
	GOD_WANTS_BAR,

	// to dump simulator terrain data to terrain.raw file
	GOD_WANTS_TERRAIN_SAVE,
	// to load simulator terrain data from terrain.raw file
	GOD_WANTS_TERRAIN_LOAD,

	GOD_WANTS_TOGGLE_AVATAR_GEOMETRY,	// HACK for testing new avatar geom

	// real-time telehub operations
	GOD_WANTS_TELEHUB_INFO,
	GOD_WANTS_CONNECT_TELEHUB,
	GOD_WANTS_DELETE_TELEHUB,
	GOD_WANTS_ADD_TELEHUB_SPAWNPOINT,
	GOD_WANTS_REMOVE_TELEHUB_SPAWNPOINT,

};

enum EIMSource
{
	IM_FROM_VIEWER,
	IM_FROM_DATASERVER,
	IM_FROM_SIM
};

extern const U8 IM_ONLINE;
extern const U8 IM_OFFLINE;

extern const S32 VOTE_YES;
extern const S32 VOTE_NO;
extern const S32 VOTE_ABSTAIN;

extern const S32 VOTE_MAJORITY;
extern const S32 VOTE_SUPER_MAJORITY;
extern const S32 VOTE_UNANIMOUS;

extern const char EMPTY_BINARY_BUCKET[];
extern const S32 EMPTY_BINARY_BUCKET_SIZE;

extern const U32 NO_TIMESTAMP;
extern const std::string SYSTEM_FROM;

// Number of retry attempts on sending the im.
extern const S32 IM_TTL;


class LLIMInfo : public LLRefCount
{
protected:
	LLIMInfo();
	~LLIMInfo();

public:
	LLIMInfo(LLMessageSystem* msg, 
			EIMSource source = IM_FROM_SIM, 
			S32 ttl = IM_TTL);

	LLIMInfo(
		const LLUUID& from_id,
		BOOL from_group,
		const LLUUID& to_id,
		EInstantMessage im_type, 
		const std::string& name,
		const std::string& message,
		const LLUUID& id,
		U32 parent_estate_id,
		const LLUUID& region_id,
		const LLVector3& position,
		LLSD data,
		U8 offline,
		U32 timestamp,
		EIMSource source,
		S32 ttl = IM_TTL);

	void packInstantMessage(LLMessageSystem* msg) const;
	void packMessageBlock(LLMessageSystem* msg) const;
	void unpackMessageBlock(LLMessageSystem* msg);
	LLPointer<LLIMInfo> clone();
public:
	LLUUID mFromID;
	BOOL mFromGroup;
	LLUUID mToID;
	U32 mParentEstateID;
	LLUUID mRegionID;
	LLVector3 mPosition;
	U8 mOffline;
	bool mViewerThinksToIsOnline;
	EInstantMessage mIMType; 
	LLUUID mID;
	U32 mTimeStamp;
	std::string mName;
	std::string mMessage;
	LLSD mData;

	EIMSource mSource;
	S32 mTTL;
};

LLPointer<LLIMInfo> llsd_to_im_info(const LLSD& im_info_sd);
LLSD im_info_to_llsd(LLPointer<LLIMInfo> im_info);

void pack_instant_message(
	LLMessageSystem* msgsystem,
	const LLUUID& from_id,
	BOOL from_group,
	const LLUUID& session_id,
	const LLUUID& to_id,
	const std::string& name,
	const std::string& message,
	U8 offline = IM_ONLINE,
	EInstantMessage dialog = IM_NOTHING_SPECIAL,
	const LLUUID& id = LLUUID::null,
	U32 parent_estate_id = 0,
	const LLUUID& region_id = LLUUID::null,
	const LLVector3& position = LLVector3::zero,
	U32 timestamp = NO_TIMESTAMP, 
	const U8* binary_bucket = (U8*)EMPTY_BINARY_BUCKET,
	S32 binary_bucket_size = EMPTY_BINARY_BUCKET_SIZE);

void pack_instant_message_block(
	LLMessageSystem* msgsystem,
	const LLUUID& from_id,
	BOOL from_group,
	const LLUUID& session_id,
	const LLUUID& to_id,
	const std::string& name,
	const std::string& message,
	U8 offline = IM_ONLINE,
	EInstantMessage dialog = IM_NOTHING_SPECIAL,
	const LLUUID& id = LLUUID::null,
	U32 parent_estate_id = 0,
	const LLUUID& region_id = LLUUID::null,
	const LLVector3& position = LLVector3::zero,
	U32 timestamp = NO_TIMESTAMP, 
	const U8* binary_bucket = (U8*)EMPTY_BINARY_BUCKET,
	S32 binary_bucket_size = EMPTY_BINARY_BUCKET_SIZE);


#endif // LL_LLINSTANTMESSAGE_H

