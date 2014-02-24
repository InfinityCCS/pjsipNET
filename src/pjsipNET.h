/* 
 * Copyright (C) 2014 Infinity CCS Ltd (http://www.infinityccs.com/)
 * Copyright (C) 2007 Sasa Coh <sasacoh@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */
 
// pjsipNET.h : Declares the entry point for the .Net GUI application.
//

#ifdef PJSIPNET_EXPORTS
	#define PJSIPNET_API __declspec(dllexport)
#else
	#define PJSIPNET_API __declspec(dllimport)
#endif


// Structure containing pjsip configuration parameters
// Should be synhronized with appropriate .Net structure!!!!!
struct SipConfigStruct
{
	int listenPort;
	bool noUDP;
	bool noTCP;
	char stunAddress[255];
	bool publishEnabled;
	int expires;

	bool VADEnabled;
	int ECTail;

	char nameServer[255];

	bool pollingEventsEnabled;

	int logLevel;

	// IMS specifics
	bool imsEnabled;
	bool imsIPSecHeaders;
	bool imsIPSecTransport;
};

// calback function definitions
typedef int __stdcall fptr_regstate(int, int);				// on registration state changed
typedef int __stdcall fptr_callstate(int, int);	// on call state changed
typedef int __stdcall fptr_callincoming(int, char*);	// on call incoming
typedef int __stdcall fptr_getconfigdata(int);	// get config data
typedef int __stdcall fptr_callholdconf(int);
typedef int __stdcall fptr_callretrieveconf(int);
typedef int __stdcall fptr_msgrec (char*, char*);
typedef int __stdcall fptr_buddystatus(int, int, const char*);
typedef int __stdcall fptr_dtmfdigit(int callId, int digit);
typedef int __stdcall fptr_mwi(int mwi, char* info);
typedef int __stdcall fptr_crep(int oldid, int newid);

// Callback registration 
extern "C" PJSIPNET_API int onRegStateCallback(fptr_regstate cb);	  // register registration notifier
extern "C" PJSIPNET_API int onCallStateCallback(fptr_callstate cb); // register call notifier
extern "C" PJSIPNET_API int onCallIncoming(fptr_callincoming cb); // register incoming call notifier
extern "C" PJSIPNET_API int onCallHoldConfirmCallback(fptr_callholdconf cb); // register call notifier
//extern "C" PJSIPNET_API int onCallRetrieveConfirm(fptr_callretrieveconf cb); // register call notifier
extern "C" PJSIPNET_API int onMessageReceivedCallback(fptr_msgrec cb); // register call notifier
extern "C" PJSIPNET_API int onBuddyStatusChangedCallback(fptr_buddystatus cb); // register call notifier
extern "C" PJSIPNET_API int onDtmfDigitCallback(fptr_dtmfdigit cb); // register dtmf digit notifier
extern "C" PJSIPNET_API int onMessageWaitingCallback(fptr_mwi cb); // register MWI notifier
extern "C" PJSIPNET_API int onCallReplaced(fptr_crep cb); // register Call replaced notifier

// pjsip common API
extern "C" PJSIPNET_API void dll_setSipConfig(SipConfigStruct* config);
extern "C" PJSIPNET_API int dll_init();
extern "C" PJSIPNET_API int dll_shutdown(); 
extern "C" PJSIPNET_API int dll_main(void);
extern "C" PJSIPNET_API int dll_getNumOfCodecs();
extern "C" PJSIPNET_API int dll_getCodec(int index, char* codec);
extern "C" PJSIPNET_API int dll_setCodecPriority(char* name, int index);
// pjsip call API
extern "C" PJSIPNET_API int dll_registerAccount(char* uri, char* reguri, char* name, char* username, 
																										char* password, char* proxy, bool isdefault);
extern "C" PJSIPNET_API int dll_makeCall(int accountId, char* uri); 
extern "C" PJSIPNET_API int dll_releaseCall(int callId); 
extern "C" PJSIPNET_API int dll_answerCall(int callId, int code);
extern "C" PJSIPNET_API int dll_holdCall(int callId);
extern "C" PJSIPNET_API int dll_retrieveCall(int callId);
extern "C" PJSIPNET_API int dll_xferCall(int callid, char* uri);
extern "C" PJSIPNET_API int dll_xferCallWithReplaces(int callId, int dstSession);
extern "C" PJSIPNET_API int dll_serviceReq(int callId, int serviceCode, const char* destUri);
extern "C" PJSIPNET_API int dll_dialDtmf(int callId, char* digits, int mode);
extern "C" PJSIPNET_API int dll_removeAccounts();
extern "C" PJSIPNET_API int dll_sendInfo(int callid, char* content);
extern "C" PJSIPNET_API int dll_getCurrentCodec(int callId, char* codec);
extern "C" PJSIPNET_API int dll_makeConference(int callId);
extern "C" PJSIPNET_API int dll_sendCallMessage(int callId, char* message);
// IM & Presence api
extern "C" PJSIPNET_API int dll_addBuddy(char* uri, bool subscribe);
extern "C" PJSIPNET_API int dll_removeBuddy(int buddyId);
extern "C" PJSIPNET_API int dll_sendMessage(int accId, char* uri, char* message);
extern "C" PJSIPNET_API int dll_setStatus(int accId, int presence_state);

extern "C" PJSIPNET_API int dll_setSoundDevice(char* playbackDeviceId, char* recordingDeviceId);

extern "C" PJSIPNET_API int dll_pollForEvents(int timeout);
