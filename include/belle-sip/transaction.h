/*
	belle-sip - SIP (RFC3261) library.
    Copyright (C) 2010  Belledonne Communications SARL

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef BELLE_SIP_TRANSACTION_H
#define BELLE_SIP_TRANSACTION_H


typedef enum belle_sip_transaction_state{
	BELLE_SIP_TRANSACTION_INIT,
	BELLE_SIP_TRANSACTION_CALLING,
	BELLE_SIP_TRANSACTION_COMPLETED,
	BELLE_SIP_TRANSACTION_CONFIRMED,
	BELLE_SIP_TRANSACTION_ACCEPTED, /*<for Invite transaction, introduced by RFC6026, fixing bugs in RFC3261*/
	BELLE_SIP_TRANSACTION_PROCEEDING,
	BELLE_SIP_TRANSACTION_TRYING,
	BELLE_SIP_TRANSACTION_TERMINATED
}belle_sip_transaction_state_t;

BELLE_SIP_BEGIN_DECLS

const char *belle_sip_transaction_state_to_string(belle_sip_transaction_state_t state);

void *belle_sip_transaction_get_application_data(const belle_sip_transaction_t *t);
void belle_sip_transaction_set_application_data(belle_sip_transaction_t *t, void *data);
const char *belle_sip_transaction_get_branch_id(const belle_sip_transaction_t *t);
belle_sip_transaction_state_t belle_sip_transaction_get_state(const belle_sip_transaction_t *t);
void belle_sip_transaction_terminate(belle_sip_transaction_t *t);
BELLESIP_EXPORT belle_sip_request_t *belle_sip_transaction_get_request(const belle_sip_transaction_t *t);
BELLESIP_EXPORT belle_sip_response_t *belle_sip_transaction_get_response(const belle_sip_transaction_t *t);
BELLESIP_EXPORT belle_sip_dialog_t*  belle_sip_transaction_get_dialog(const belle_sip_transaction_t *t);

BELLESIP_EXPORT void belle_sip_server_transaction_send_response(belle_sip_server_transaction_t *t, belle_sip_response_t *resp);

belle_sip_request_t * belle_sip_client_transaction_create_cancel(belle_sip_client_transaction_t *t);
BELLESIP_EXPORT int belle_sip_client_transaction_send_request(belle_sip_client_transaction_t *t);
/*
 * Same as #belle_sip_client_transaction_send_request but with a predefined route.
 * @param  t  belle_sip_client_transaction_t
 * @param outbound_proxy uri use to directly send the request, useful for outbound proxy.
 * */
BELLESIP_EXPORT int belle_sip_client_transaction_send_request_to(belle_sip_client_transaction_t *t,belle_sip_uri_t* outbound_proxy);

/**
 * Creates an a sip refresher for transaction like REGISTER/SUBSCRIBE or INVITE which could be refreshed.
 * Transaction must in be in stated BELLE_SIP_TRANSACTION_COMPLETED. Refresher is created and started. A ref is taken on object transaction
 * */
BELLESIP_EXPORT belle_sip_refresher_t* belle_sip_client_transaction_create_refresher(belle_sip_client_transaction_t *t);
/**
 * Create an authenticated request based on an existing terminated transaction.
 * <br>This function, update cseq, put route set and try to fill authorization headers. Initial request is not cloned.
 * @param transaction . must be in state completed
 * */
BELLESIP_EXPORT belle_sip_request_t* belle_sip_client_transaction_create_authenticated_request(belle_sip_client_transaction_t *t);

#define BELLE_SIP_TRANSACTION(t) BELLE_SIP_CAST(t,belle_sip_transaction_t)
#define BELLE_SIP_SERVER_TRANSACTION(t) BELLE_SIP_CAST(t,belle_sip_server_transaction_t)
#define BELLE_SIP_CLIENT_TRANSACTION(t) BELLE_SIP_CAST(t,belle_sip_client_transaction_t)


BELLE_SIP_END_DECLS

#endif

