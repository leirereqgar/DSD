/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static res_calculo *
_suma_1 (suma_1_argument *argp, struct svc_req *rqstp)
{
	return (suma_1_svc(argp->arg1, argp->arg2, rqstp));
}

static res_calculo *
_resta_1 (resta_1_argument *argp, struct svc_req *rqstp)
{
	return (resta_1_svc(argp->arg1, argp->arg2, rqstp));
}

static res_calculo *
_multiplicacion_1 (multiplicacion_1_argument *argp, struct svc_req *rqstp)
{
	return (multiplicacion_1_svc(argp->arg1, argp->arg2, rqstp));
}

static res_calculo *
_division_1 (division_1_argument *argp, struct svc_req *rqstp)
{
	return (division_1_svc(argp->arg1, argp->arg2, rqstp));
}

static res_calculo_vectores *
_sumavector_1 (sumavector_1_argument *argp, struct svc_req *rqstp)
{
	return (sumavector_1_svc(argp->arg1, argp->arg2, rqstp));
}

static res_calculo_vectores *
_restavector_1 (restavector_1_argument *argp, struct svc_req *rqstp)
{
	return (restavector_1_svc(argp->arg1, argp->arg2, rqstp));
}

static res_calculo_vectores *
_multiplicacionvector_1 (multiplicacionvector_1_argument *argp, struct svc_req *rqstp)
{
	return (multiplicacionvector_1_svc(argp->arg1, argp->arg2, rqstp));
}

static res_calculo_vectores *
_multiplicacionescalar_1 (multiplicacionescalar_1_argument *argp, struct svc_req *rqstp)
{
	return (multiplicacionescalar_1_svc(argp->arg1, argp->arg2, rqstp));
}

static res_calculo_matrices *
_sumamatriz_1 (sumamatriz_1_argument *argp, struct svc_req *rqstp)
{
	return (sumamatriz_1_svc(argp->arg1, argp->arg2, rqstp));
}

static res_calculo_matrices *
_restamatriz_1 (restamatriz_1_argument *argp, struct svc_req *rqstp)
{
	return (restamatriz_1_svc(argp->arg1, argp->arg2, rqstp));
}

static res_calculo_matrices *
_multiplicacionmatriz_1 (multiplicacionmatriz_1_argument *argp, struct svc_req *rqstp)
{
	return (multiplicacionmatriz_1_svc(argp->arg1, argp->arg2, rqstp));
}

static res_calculo_matrices *
_multiplicacionmatrizescalar_1 (multiplicacionmatrizescalar_1_argument *argp, struct svc_req *rqstp)
{
	return (multiplicacionmatrizescalar_1_svc(argp->arg1, argp->arg2, rqstp));
}

static void
calculadoraprog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		suma_1_argument suma_1_arg;
		resta_1_argument resta_1_arg;
		multiplicacion_1_argument multiplicacion_1_arg;
		division_1_argument division_1_arg;
		sumavector_1_argument sumavector_1_arg;
		restavector_1_argument restavector_1_arg;
		multiplicacionvector_1_argument multiplicacionvector_1_arg;
		multiplicacionescalar_1_argument multiplicacionescalar_1_arg;
		sumamatriz_1_argument sumamatriz_1_arg;
		restamatriz_1_argument restamatriz_1_arg;
		multiplicacionmatriz_1_argument multiplicacionmatriz_1_arg;
		multiplicacionmatrizescalar_1_argument multiplicacionmatrizescalar_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case SUMA:
		_xdr_argument = (xdrproc_t) xdr_suma_1_argument;
		_xdr_result = (xdrproc_t) xdr_res_calculo;
		local = (char *(*)(char *, struct svc_req *)) _suma_1;
		break;

	case RESTA:
		_xdr_argument = (xdrproc_t) xdr_resta_1_argument;
		_xdr_result = (xdrproc_t) xdr_res_calculo;
		local = (char *(*)(char *, struct svc_req *)) _resta_1;
		break;

	case MULTIPLICACION:
		_xdr_argument = (xdrproc_t) xdr_multiplicacion_1_argument;
		_xdr_result = (xdrproc_t) xdr_res_calculo;
		local = (char *(*)(char *, struct svc_req *)) _multiplicacion_1;
		break;

	case DIVISION:
		_xdr_argument = (xdrproc_t) xdr_division_1_argument;
		_xdr_result = (xdrproc_t) xdr_res_calculo;
		local = (char *(*)(char *, struct svc_req *)) _division_1;
		break;

	case SUMAVECTOR:
		_xdr_argument = (xdrproc_t) xdr_sumavector_1_argument;
		_xdr_result = (xdrproc_t) xdr_res_calculo_vectores;
		local = (char *(*)(char *, struct svc_req *)) _sumavector_1;
		break;

	case RESTAVECTOR:
		_xdr_argument = (xdrproc_t) xdr_restavector_1_argument;
		_xdr_result = (xdrproc_t) xdr_res_calculo_vectores;
		local = (char *(*)(char *, struct svc_req *)) _restavector_1;
		break;

	case MULTIPLICACIONVECTOR:
		_xdr_argument = (xdrproc_t) xdr_multiplicacionvector_1_argument;
		_xdr_result = (xdrproc_t) xdr_res_calculo_vectores;
		local = (char *(*)(char *, struct svc_req *)) _multiplicacionvector_1;
		break;

	case MULTIPLICACIONESCALAR:
		_xdr_argument = (xdrproc_t) xdr_multiplicacionescalar_1_argument;
		_xdr_result = (xdrproc_t) xdr_res_calculo_vectores;
		local = (char *(*)(char *, struct svc_req *)) _multiplicacionescalar_1;
		break;

	case SUMAMATRIZ:
		_xdr_argument = (xdrproc_t) xdr_sumamatriz_1_argument;
		_xdr_result = (xdrproc_t) xdr_res_calculo_matrices;
		local = (char *(*)(char *, struct svc_req *)) _sumamatriz_1;
		break;

	case RESTAMATRIZ:
		_xdr_argument = (xdrproc_t) xdr_restamatriz_1_argument;
		_xdr_result = (xdrproc_t) xdr_res_calculo_matrices;
		local = (char *(*)(char *, struct svc_req *)) _restamatriz_1;
		break;

	case MULTIPLICACIONMATRIZ:
		_xdr_argument = (xdrproc_t) xdr_multiplicacionmatriz_1_argument;
		_xdr_result = (xdrproc_t) xdr_res_calculo_matrices;
		local = (char *(*)(char *, struct svc_req *)) _multiplicacionmatriz_1;
		break;

	case MULTIPLICACIONMATRIZESCALAR:
		_xdr_argument = (xdrproc_t) xdr_multiplicacionmatrizescalar_1_argument;
		_xdr_result = (xdrproc_t) xdr_res_calculo_matrices;
		local = (char *(*)(char *, struct svc_req *)) _multiplicacionmatrizescalar_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (CALCULADORAPROG, CALCULADORAVER);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, CALCULADORAPROG, CALCULADORAVER, calculadoraprog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (CALCULADORAPROG, CALCULADORAVER, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, CALCULADORAPROG, CALCULADORAVER, calculadoraprog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (CALCULADORAPROG, CALCULADORAVER, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
