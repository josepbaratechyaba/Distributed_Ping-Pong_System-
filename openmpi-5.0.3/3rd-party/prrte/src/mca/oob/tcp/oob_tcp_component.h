/*
 * Copyright (c) 2004-2007 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2006 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2005 High Performance Computing Center Stuttgart,
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * Copyright (c) 2006-2013 Los Alamos National Security, LLC.
 *                         All rights reserved.
 * Copyright (c) 2010-2020 Cisco Systems, Inc.  All rights reserved
 * Copyright (c) 2014-2019 Intel, Inc.  All rights reserved.
 * Copyright (c) 2019      Research Organization for Information Science
 *                         and Technology (RIST).  All rights reserved.
 * Copyright (c) 2020      Amazon.com, Inc. or its affiliates.  All Rights
 *                         reserved.
 * Copyright (c) 2021-2022 Nanook Consulting.  All rights reserved.
 * Copyright (c) 2023      Triad National Security, LLC. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

#ifndef _MCA_OOB_TCP_COMPONENT_H_
#define _MCA_OOB_TCP_COMPONENT_H_

#include "prte_config.h"

#ifdef HAVE_SYS_TIME_H
#    include <sys/time.h>
#endif

#include "src/include/prte_stdatomic.h"
#include "src/class/pmix_bitmap.h"
#include "src/class/pmix_list.h"
#include "src/class/pmix_pointer_array.h"
#include "src/event/event-internal.h"

#include "oob_tcp.h"
#include "src/mca/oob/oob.h"

/**
 *  OOB TCP Component
 */
typedef struct {
    prte_oob_base_component_t super; /**< base OOB component */
    uint32_t addr_count;             /**< total number of addresses */
    int num_links;                   /**< number of logical links per physical device */
    int max_retries;                 /**< max number of retries before declaring peer gone */
    pmix_list_t events;              /**< events for monitoring connections */
    int peer_limit;                  /**< max size of tcp peer cache */
    pmix_list_t peers;               // connection addresses for peers

    /* Port specifications */
    int tcp_sndbuf;   /**< socket send buffer size */
    int tcp_rcvbuf;   /**< socket recv buffer size */

    /* IPv4 support */
    bool disable_ipv4_family; /**< disable this AF */
    char **tcp_static_ports;  /**< Static ports - IPV4 */
    char **tcp_dyn_ports;     /**< Dynamic ports - IPV4 */
    char **ipv4conns;
    char **ipv4ports;

    /* IPv6 support */
    bool disable_ipv6_family; /**< disable this AF */
    char **tcp6_static_ports; /**< Static ports - IPV6 */
    char **tcp6_dyn_ports;    /**< Dynamic ports - IPV6 */
    char **ipv6conns;
    char **ipv6ports;

    /* connection support */
    pmix_list_t local_ifs; /**< prte list of local pmix_pif_t interfaces */
    char **if_masks;
    char *my_uri;                /**< uri for connecting to the TCP module */
    int num_hnp_ports;           /**< number of ports the HNP should listen on */
    pmix_list_t listeners;       /**< List of sockets being monitored by event or thread */
    pmix_thread_t listen_thread; /**< handle to the listening thread */
    prte_atomic_bool_t listen_thread_active;
    struct timeval listen_thread_tv; /**< Timeout when using listen thread */
    int stop_thread[2];              /**< pipe used to exit the listen thread */
    int keepalive_probes;   /**< number of keepalives that can be missed before declaring error */
    int keepalive_time;     /**< idle time in seconds before starting to send keepalives */
    int keepalive_intvl;    /**< time between keepalives, in seconds */
    int retry_delay;        /**< time to wait before retrying connection */
    int max_recon_attempts; /**< maximum number of times to attempt connect before giving up (-1 for
                               never) */
} prte_mca_oob_tcp_component_t;

PRTE_MODULE_EXPORT extern prte_mca_oob_tcp_component_t prte_mca_oob_tcp_component;

PRTE_MODULE_EXPORT void prte_mca_oob_tcp_component_set_module(int fd, short args, void *cbdata);
PRTE_MODULE_EXPORT void prte_mca_oob_tcp_component_lost_connection(int fd, short args, void *cbdata);
PRTE_MODULE_EXPORT void prte_mca_oob_tcp_component_failed_to_connect(int fd, short args, void *cbdata);
PRTE_MODULE_EXPORT void prte_mca_oob_tcp_component_no_route(int fd, short args, void *cbdata);
PRTE_MODULE_EXPORT void prte_mca_oob_tcp_component_hop_unknown(int fd, short args, void *cbdata);

#endif /* _MCA_OOB_TCP_COMPONENT_H_ */
