#include "paxos.h"
#include "paxos_xdr.h"

bool_t
xdr_iid_t(XDR *xdrs, iid_t *objp)
{

	if (!xdr_u_int32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_ballot_t(XDR *xdrs, ballot_t *objp)
{

	if (!xdr_u_int32_t(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_paxos_value(XDR *xdrs, paxos_value *objp)
{

	if (!xdr_bytes(xdrs, (char **)&objp->paxos_value_val, (u_int *)&objp->paxos_value_len, PAXOS_MAX_VALUE_SIZE))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_paxos_value_ballot(XDR *xdrs, paxos_value_ballot *objp)
{

	if (!xdr_ballot_t(xdrs, &objp->ballot))
		return (FALSE);
	if (!xdr_paxos_value(xdrs, &objp->value))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_paxos_prepare(XDR *xdrs, paxos_prepare *objp)
{

	if (!xdr_iid_t(xdrs, &objp->iid))
		return (FALSE);
	if (!xdr_ballot_t(xdrs, &objp->ballot))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_paxos_promise(XDR *xdrs, paxos_promise *objp)
{

	if (!xdr_iid_t(xdrs, &objp->iid))
		return (FALSE);
	if (!xdr_ballot_t(xdrs, &objp->ballot))
		return (FALSE);
	if (!xdr_pointer(xdrs, (char **)&objp->value, sizeof(paxos_value_ballot), (xdrproc_t)xdr_paxos_value_ballot))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_paxos_accept(XDR *xdrs, paxos_accept *objp)
{

	if (!xdr_iid_t(xdrs, &objp->iid))
		return (FALSE);
	if (!xdr_ballot_t(xdrs, &objp->ballot))
		return (FALSE);
	if (!xdr_paxos_value(xdrs, &objp->value))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_paxos_accepted(XDR *xdrs, paxos_accepted *objp)
{

	if (!xdr_iid_t(xdrs, &objp->iid))
		return (FALSE);
	if (!xdr_ballot_t(xdrs, &objp->ballot))
		return (FALSE);
	if (!xdr_ballot_t(xdrs, &objp->value_ballot))
		return (FALSE);
	if (!xdr_paxos_value(xdrs, &objp->value))
		return (FALSE);
	if (!xdr_int16_t(xdrs, &objp->is_final))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_paxos_repeat(XDR *xdrs, paxos_repeat *objp)
{

	if (!xdr_iid_t(xdrs, &objp->from))
		return (FALSE);
	if (!xdr_iid_t(xdrs, &objp->to))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_paxos_client_value(XDR *xdrs, paxos_client_value *objp)
{

	if (!xdr_paxos_value(xdrs, &objp->value))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_paxos_message_type(XDR *xdrs, paxos_message_type *objp)
{

	if (!xdr_enum(xdrs, (enum_t *)objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_paxos_message(XDR *xdrs, paxos_message *objp)
{

	if (!xdr_paxos_message_type(xdrs, &objp->type))
		return (FALSE);
	switch (objp->type) {
	case PAXOS_PREPARE:
		if (!xdr_paxos_prepare(xdrs, &objp->paxos_message_u.prepare))
			return (FALSE);
		break;
	case PAXOS_PROMISE:
		if (!xdr_paxos_promise(xdrs, &objp->paxos_message_u.promise))
			return (FALSE);
		break;
	case PAXOS_ACCEPT:
		if (!xdr_paxos_accept(xdrs, &objp->paxos_message_u.accept))
			return (FALSE);
		break;
	case PAXOS_ACCEPTED:
		if (!xdr_paxos_accepted(xdrs, &objp->paxos_message_u.accepted))
			return (FALSE);
		break;
	case PAXOS_REPEAT:
		if (!xdr_paxos_repeat(xdrs, &objp->paxos_message_u.repeat))
			return (FALSE);
		break;
	case PAXOS_CLIENT_VALUE:
		if (!xdr_paxos_client_value(xdrs, &objp->paxos_message_u.client_value))
			return (FALSE);
		break;
	default:
		break;
	}
	return (TRUE);
}