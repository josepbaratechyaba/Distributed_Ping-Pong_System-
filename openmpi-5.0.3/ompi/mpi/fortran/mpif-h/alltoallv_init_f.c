/*
 * Copyright (c) 2004-2005 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2021 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2005 High Performance Computing Center Stuttgart,
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * Copyright (c) 2011-2012 Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2015-2021 Research Organization for Information Science
 *                         and Technology (RIST).  All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

#include "ompi_config.h"

#include "ompi/mpi/fortran/mpif-h/bindings.h"
#include "ompi/mpi/fortran/base/constants.h"
#include "ompi/mca/coll/base/coll_base_util.h"

#if OMPI_BUILD_MPI_PROFILING
#if OPAL_HAVE_WEAK_SYMBOLS
#pragma weak PMPI_ALLTOALLV_INIT = ompi_alltoallv_init_f
#pragma weak pmpi_alltoallv_init = ompi_alltoallv_init_f
#pragma weak pmpi_alltoallv_init_ = ompi_alltoallv_init_f
#pragma weak pmpi_alltoallv_init__ = ompi_alltoallv_init_f

#pragma weak PMPI_Alltoallv_init_f = ompi_alltoallv_init_f
#pragma weak PMPI_Alltoallv_init_f08 = ompi_alltoallv_init_f
#else
OMPI_GENERATE_F77_BINDINGS (PMPI_ALLTOALLV_INIT,
                            pmpi_alltoallv_init,
                            pmpi_alltoallv_init_,
                            pmpi_alltoallv_init__,
                            pompi_alltoallv_init_f,
                            (char *sendbuf, MPI_Fint *sendcounts, MPI_Fint *sdispls, MPI_Fint *sendtype, char *recvbuf, MPI_Fint *recvcounts, MPI_Fint *rdispls, MPI_Fint *recvtype, MPI_Fint *comm, MPI_Fint *info, MPI_Fint *request, MPI_Fint *ierr),
                            (sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request, ierr) )
#endif
#endif

#if OPAL_HAVE_WEAK_SYMBOLS
#pragma weak MPI_ALLTOALLV_INIT = ompi_alltoallv_init_f
#pragma weak mpi_alltoallv_init = ompi_alltoallv_init_f
#pragma weak mpi_alltoallv_init_ = ompi_alltoallv_init_f
#pragma weak mpi_alltoallv_init__ = ompi_alltoallv_init_f

#pragma weak MPI_Alltoallv_init_f = ompi_alltoallv_init_f
#pragma weak MPI_Alltoallv_init_f08 = ompi_alltoallv_init_f
#else
#if ! OMPI_BUILD_MPI_PROFILING
OMPI_GENERATE_F77_BINDINGS (MPI_ALLTOALLV_INIT,
                            mpi_alltoallv_init,
                            mpi_alltoallv_init_,
                            mpi_alltoallv_init__,
                            ompi_alltoallv_init_f,
                            (char *sendbuf, MPI_Fint *sendcounts, MPI_Fint *sdispls, MPI_Fint *sendtype, char *recvbuf, MPI_Fint *recvcounts, MPI_Fint *rdispls, MPI_Fint *recvtype, MPI_Fint *comm, MPI_Fint *info, MPI_Fint *request, MPI_Fint *ierr),
                            (sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, info, request, ierr) )
#else
#define ompi_alltoallv_init_f pompi_alltoallv_init_f
#endif
#endif


void ompi_alltoallv_init_f(char *sendbuf, MPI_Fint *sendcounts, MPI_Fint *sdispls,
                           MPI_Fint *sendtype, char *recvbuf, MPI_Fint *recvcounts,
                           MPI_Fint *rdispls, MPI_Fint *recvtype,
                           MPI_Fint *comm, MPI_Fint *info, MPI_Fint *request, MPI_Fint *ierr)
{
    MPI_Comm c_comm;
    MPI_Datatype c_sendtype, c_recvtype;
    MPI_Info c_info;
    MPI_Request c_request;
    int size, idx = 0, c_ierr;
    OMPI_ARRAY_NAME_DECL(sendcounts);
    OMPI_ARRAY_NAME_DECL(sdispls);
    OMPI_ARRAY_NAME_DECL(recvcounts);
    OMPI_ARRAY_NAME_DECL(rdispls);

    c_comm = PMPI_Comm_f2c(*comm);
    c_sendtype = PMPI_Type_f2c(*sendtype);
    c_recvtype = PMPI_Type_f2c(*recvtype);
    c_info = PMPI_Info_f2c(*info);

    PMPI_Comm_size(c_comm, &size);
    OMPI_ARRAY_FINT_2_INT(sendcounts, size);
    OMPI_ARRAY_FINT_2_INT(sdispls, size);
    OMPI_ARRAY_FINT_2_INT(recvcounts, size);
    OMPI_ARRAY_FINT_2_INT(rdispls, size);

    sendbuf = (char *) OMPI_F2C_IN_PLACE(sendbuf);
    sendbuf = (char *) OMPI_F2C_BOTTOM(sendbuf);
    recvbuf = (char *) OMPI_F2C_BOTTOM(recvbuf);

    c_ierr = PMPI_Alltoallv_init(sendbuf,
                                 OMPI_ARRAY_NAME_CONVERT(sendcounts),
                                 OMPI_ARRAY_NAME_CONVERT(sdispls),
                                 c_sendtype,
                                 recvbuf,
                                 OMPI_ARRAY_NAME_CONVERT(recvcounts),
                                 OMPI_ARRAY_NAME_CONVERT(rdispls),
                                 c_recvtype, c_comm, c_info, &c_request);
    if (NULL != ierr) *ierr = OMPI_INT_2_FINT(c_ierr);
    if (MPI_SUCCESS == c_ierr) {
        *request = PMPI_Request_c2f(c_request);
        ompi_coll_base_nbc_request_t* nb_request = (ompi_coll_base_nbc_request_t*)c_request;
        if (sendcounts != OMPI_ARRAY_NAME_CONVERT(sendcounts)) {
            nb_request->data.release_arrays[idx++] = OMPI_ARRAY_NAME_CONVERT(sendcounts);
            nb_request->data.release_arrays[idx++] = OMPI_ARRAY_NAME_CONVERT(sdispls);
            nb_request->data.release_arrays[idx++] = OMPI_ARRAY_NAME_CONVERT(recvcounts);
            nb_request->data.release_arrays[idx++] = OMPI_ARRAY_NAME_CONVERT(rdispls);
        }
        nb_request->data.release_arrays[idx]   = NULL;
    } else {
        OMPI_ARRAY_FINT_2_INT_CLEANUP(sendcounts);
        OMPI_ARRAY_FINT_2_INT_CLEANUP(sdispls);
        OMPI_ARRAY_FINT_2_INT_CLEANUP(recvcounts);
        OMPI_ARRAY_FINT_2_INT_CLEANUP(rdispls);
    }
}
