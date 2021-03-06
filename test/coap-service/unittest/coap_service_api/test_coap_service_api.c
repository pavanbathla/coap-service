/*
 * Copyright (c) 2015 ARM Limited. All Rights Reserved.
 */
#include "test_coap_service_api.h"
#include <string.h>
#include "coap_service_api.h"
#include "nsdynmemLIB_stub.h"
#include "coap_connection_handler_stub.h"
#include "coap_message_handler_stub.h"
#include "eventOS_event_stub.h"
#include "eventOS_event.h"
#include "net_interface.h"

int sec_done_cb(int8_t service_id, uint8_t address[static 16], uint8_t keyblock[static 40]){
    return 2;
}

int sec_start_cb(int8_t service_id, uint8_t address[static 16], uint16_t port, uint8_t* pw, uint8_t *pw_len)
{
    return 2;
}

int request_recv_cb(int8_t service_id, uint8_t source_address[static 16], uint16_t source_port, sn_coap_hdr_s *request_ptr)
{
    return 2;
}

int virtual_sock_send_cb(int8_t service_id, uint8_t destination_addr_ptr[static 16], uint16_t port, const uint8_t *data_ptr, uint16_t data_len)
{
    return 2;
}

bool test_coap_service_initialize()
{
    if( -1 != coap_service_initialize(1, 2, 0, NULL, NULL ))
        return false;


    nsdynmemlib_stub.returnCounter = 1;
    thread_conn_handler_stub.handler_obj = NULL;
    if( -1 != coap_service_initialize(1, 2, 0, NULL, NULL ))
        return false;

    thread_conn_handler_stub.handler_obj = (coap_conn_handler_t*)malloc(sizeof(coap_conn_handler_t));
    memset(thread_conn_handler_stub.handler_obj, 0, sizeof(coap_conn_handler_t));
    coap_message_handler_stub.coap_ptr = NULL;

    nsdynmemlib_stub.returnCounter = 1;
    thread_conn_handler_stub.int_value = -1;
    if( -1 != coap_service_initialize(1, 2, 0, NULL, NULL ))
            return false;

    thread_conn_handler_stub.handler_obj = (coap_conn_handler_t*)malloc(sizeof(coap_conn_handler_t));
    memset(thread_conn_handler_stub.handler_obj, 0, sizeof(coap_conn_handler_t));
    nsdynmemlib_stub.returnCounter = 1;
    thread_conn_handler_stub.int_value = 0;

    if( 1 != coap_service_initialize(1, 2, 0, NULL, NULL ))
        return false;

    nsdynmemlib_stub.returnCounter = 1;
    if( 2 != coap_service_initialize(3, 4, 0, NULL, NULL ))
        return false;

    coap_service_delete(2);
    coap_service_delete(1);

    free( thread_conn_handler_stub.handler_obj );
    thread_conn_handler_stub.handler_obj = NULL;
    return true;
}

bool test_coap_service_delete()
{
    coap_service_delete(1);

    thread_conn_handler_stub.handler_obj = (coap_conn_handler_t*)malloc(sizeof(coap_conn_handler_t));
    memset(thread_conn_handler_stub.handler_obj, 0, sizeof(coap_conn_handler_t));
    nsdynmemlib_stub.returnCounter = 1;
    coap_message_handler_stub.coap_ptr = NULL;

    if( 1 != coap_service_initialize(1, 2, 0, NULL, NULL ))
        return false;

    coap_service_delete(1);

    free( thread_conn_handler_stub.handler_obj );
    thread_conn_handler_stub.handler_obj = NULL;

    return true;
}

bool test_coap_service_virtual_socket_recv()
{
    uint8_t buf[16];
    if( -1 != coap_service_virtual_socket_recv(1, &buf, 10, NULL, 0) )
        return false;

    thread_conn_handler_stub.handler_obj = (coap_conn_handler_t*)malloc(sizeof(coap_conn_handler_t));
    memset(thread_conn_handler_stub.handler_obj, 0, sizeof(coap_conn_handler_t));
    nsdynmemlib_stub.returnCounter = 1;
    coap_message_handler_stub.coap_ptr = NULL;

    if( 1 != coap_service_initialize(1, 2, 0, NULL, NULL ))
        return false;

    thread_conn_handler_stub.int_value = 5;
    if( 5 != coap_service_virtual_socket_recv(1, &buf, 10, NULL, 0) )
        return false;

    coap_service_delete(1);

    free( thread_conn_handler_stub.handler_obj );
    thread_conn_handler_stub.handler_obj = NULL;

    thread_conn_handler_stub.int_value = 0;

    return true;
}

bool test_coap_service_virtual_socket_set_cb()
{
    if( -1 != coap_service_virtual_socket_set_cb(1, NULL) )
        return false;

    thread_conn_handler_stub.handler_obj = (coap_conn_handler_t*)malloc(sizeof(coap_conn_handler_t));
    memset(thread_conn_handler_stub.handler_obj, 0, sizeof(coap_conn_handler_t));
    nsdynmemlib_stub.returnCounter = 1;
    coap_message_handler_stub.coap_ptr = NULL;

    if( 1 != coap_service_initialize(1, 2, 0, NULL, NULL ))
        return false;

    if( 0 != coap_service_virtual_socket_set_cb(1, NULL) )
        return false;

    coap_service_delete(1);

    free( thread_conn_handler_stub.handler_obj );
    thread_conn_handler_stub.handler_obj = NULL;

    return true;
}

bool test_coap_service_register_uri()
{
    if( -1 != coap_service_register_uri(1, "as", 1, &request_recv_cb))
        return false;

    thread_conn_handler_stub.handler_obj = (coap_conn_handler_t*)malloc(sizeof(coap_conn_handler_t));
    memset(thread_conn_handler_stub.handler_obj, 0, sizeof(coap_conn_handler_t));
    nsdynmemlib_stub.returnCounter = 1;
    coap_message_handler_stub.coap_ptr = NULL;

    if( 1 != coap_service_initialize(1, 2, 0, NULL, NULL ))
        return false;

    if( -2 != coap_service_register_uri(1, "as", 1, &request_recv_cb) )
        return false;

    nsdynmemlib_stub.returnCounter = 1;
    if( -2 != coap_service_register_uri(1, "as", 1, &request_recv_cb) )
        return false;

    nsdynmemlib_stub.returnCounter = 2;
    if( 0 != coap_service_register_uri(1, "as", 1, &request_recv_cb) )
        return false;

    coap_service_delete(1);

    free( thread_conn_handler_stub.handler_obj );
    thread_conn_handler_stub.handler_obj = NULL;

    return true;
}

bool test_coap_service_unregister_uri()
{
    if( -1 != coap_service_unregister_uri(1, "as"))
        return false;

    thread_conn_handler_stub.handler_obj = (coap_conn_handler_t*)malloc(sizeof(coap_conn_handler_t));
    memset(thread_conn_handler_stub.handler_obj, 0, sizeof(coap_conn_handler_t));
    nsdynmemlib_stub.returnCounter = 1;
    coap_message_handler_stub.coap_ptr = NULL;
    thread_conn_handler_stub.int_value = 0;

    if( 1 != coap_service_initialize(1, 2, 0, NULL, NULL ))
        return false;

    nsdynmemlib_stub.returnCounter = 2;
    if( 0 != coap_service_register_uri(1, "as", 1, &request_recv_cb) )
        return false;

    if( -2 != coap_service_unregister_uri(1, "ts") )
        return false;

    if( 0 != coap_service_unregister_uri(1, "as") )
        return false;

    coap_service_delete(1);

    free( thread_conn_handler_stub.handler_obj );
    thread_conn_handler_stub.handler_obj = NULL;

    return true;
}

bool test_coap_service_request_send()
{
    uint8_t buf[16];
    coap_message_handler_stub.uint16_value = 6;
    if( 6 != coap_service_request_send(0,0,&buf,0,0,0,NULL, 0,NULL,0,NULL))
        return false;
    return true;
}

bool test_coap_service_request_delete()
{
    if( 0 != coap_service_request_delete(NULL,0))
        return false;
    return true;
}

bool test_coap_service_response_send()
{
    uint8_t buf[16];
    coap_message_handler_stub.int8_value = 6;
    if( 6 != coap_service_response_send(0,0,NULL, 65, 0,NULL, 0))
        return false;
    return true;
}

bool test_coap_callbacks()
{
    thread_conn_handler_stub.handler_obj = (coap_conn_handler_t*)malloc(sizeof(coap_conn_handler_t));
    memset(thread_conn_handler_stub.handler_obj, 0, sizeof(coap_conn_handler_t));
    nsdynmemlib_stub.returnCounter = 1;
    coap_message_handler_stub.coap_ptr = (coap_msg_handler_t *)malloc(sizeof(coap_msg_handler_t));
    memset(coap_message_handler_stub.coap_ptr, 0, sizeof(coap_msg_handler_t));

    if( 1 != coap_service_initialize(1, 2, 0, NULL, NULL ))
        return false;

    if( 0 != coap_message_handler_stub.coap_ptr->sn_coap_service_malloc(0))
        return false;

    nsdynmemlib_stub.returnCounter = 1;
    void *handle = coap_message_handler_stub.coap_ptr->sn_coap_service_malloc(5);
    if( 0 == handle )
        return false;

    coap_message_handler_stub.coap_ptr->sn_coap_service_free(handle);

    //coap_tx_function
    uint8_t data[14];
    memset(&data, 3, 14);
    sn_nsdl_addr_s addr;
    addr.addr_len = 2;
    addr.port = 4;
    addr.addr_ptr = &data;
    if( 0 != coap_message_handler_stub.coap_ptr->sn_coap_tx_callback(NULL, 0, &addr, NULL))
        return false;

    coap_transaction_t *tr = (coap_transaction_t *)malloc(sizeof(coap_transaction_t));
    memset(tr, 0, sizeof(coap_transaction_t));

    if( 0 != coap_message_handler_stub.coap_ptr->sn_coap_tx_callback(&data, 0, &addr, tr))
        return false;

    tr->service_id = 1;
    thread_conn_handler_stub.int_value = -2;
    if( 0 != coap_message_handler_stub.coap_ptr->sn_coap_tx_callback(&data, 0, &addr, tr))
        return false;

    nsdynmemlib_stub.returnCounter = 1;
    if( 0 != coap_message_handler_stub.coap_ptr->sn_coap_tx_callback(&data, 2, &addr, tr))
        return false;

    free(tr->data_ptr);
    free(tr);

    coap_service_delete(1);

    free( coap_message_handler_stub.coap_ptr );
    coap_message_handler_stub.coap_ptr = NULL;

    free( thread_conn_handler_stub.handler_obj );
    thread_conn_handler_stub.handler_obj = NULL;

    return true;
}

#define COAP_TICK_TIMER 0xf1 //MUST BE SAME AS IN coap_service_api.c
bool test_eventOS_callbacks()
{
    thread_conn_handler_stub.handler_obj = (coap_conn_handler_t*)malloc(sizeof(coap_conn_handler_t));
    memset(thread_conn_handler_stub.handler_obj, 0, sizeof(coap_conn_handler_t));
    nsdynmemlib_stub.returnCounter = 1;
    if( 1 != coap_service_initialize(1, 2, 0, NULL, NULL ))
        return false;

    if( eventOs_event_stub.event_ptr ){
        arm_event_s event;
        event.event_type = ARM_LIB_TASKLET_INIT_EVENT;
        eventOs_event_stub.event_ptr(&event);

        event.event_type = ARM_LIB_SYSTEM_TIMER_EVENT;
        event.event_id = COAP_TICK_TIMER;
        eventOs_event_stub.event_ptr(&event);
    }

    coap_service_delete(1);
    free( thread_conn_handler_stub.handler_obj );
    thread_conn_handler_stub.handler_obj = NULL;
    return true;
}

bool test_conn_handler_callbacks()
{
    uint8_t buf[16];
    thread_conn_handler_stub.handler_obj = (coap_conn_handler_t*)malloc(sizeof(coap_conn_handler_t));
    memset(thread_conn_handler_stub.handler_obj, 0, sizeof(coap_conn_handler_t));
    nsdynmemlib_stub.returnCounter = 1;
    if( 1 != coap_service_initialize(1, 2, COAP_SERVICE_OPTIONS_SECURE_BYPASS, &sec_start_cb, &sec_done_cb ))
        return false;

    if( thread_conn_handler_stub.send_to_sock_cb ){
        thread_conn_handler_stub.bool_value = true;
        coap_service_virtual_socket_set_cb(1, &virtual_sock_send_cb);
        if( 2 != thread_conn_handler_stub.send_to_sock_cb(1, buf, 12, NULL, 0))
            return false;
        thread_conn_handler_stub.bool_value = false;
        if( -1 != thread_conn_handler_stub.send_to_sock_cb(1, buf, 12, NULL, 0))
            return false;
    }

    if( thread_conn_handler_stub.receive_from_sock_cb ){
        coap_message_handler_stub.int16_value = 2;
        if( -1 != thread_conn_handler_stub.receive_from_sock_cb(1, buf, 12, NULL, NULL, 0))
            return false;

        nsdynmemlib_stub.returnCounter = 1;
        uint8_t * ptr = ns_dyn_mem_alloc(5);
        memset(ptr, 3, 5);
        nsdynmemlib_stub.returnCounter = 1;
        if( 2 != thread_conn_handler_stub.receive_from_sock_cb(1, buf, 12, NULL, ptr, 5))
            return false;
        ns_dyn_mem_free(ptr);
        coap_message_handler_stub.int16_value = 0;

        //This could be moved to own test function,
        //but thread_conn_handler_stub.receive_from_sock_cb must be called successfully
        if( coap_message_handler_stub.cb ){
            if( -1 != coap_message_handler_stub.cb(1, NULL, NULL) )
                return false;

            sn_coap_hdr_s * coap = (sn_coap_hdr_s *)malloc(sizeof(sn_coap_hdr_s));
            memset(coap, 0, sizeof(sn_coap_hdr_s));

            uint8_t  uri[2] = "as";
            coap->uri_path_ptr = &uri;
            coap->uri_path_len=2;

            if( -1 != coap_message_handler_stub.cb(1, coap, NULL) )
                return false;

            thread_conn_handler_stub.bool_value = true;
            nsdynmemlib_stub.returnCounter = 2;
            if( 0 != coap_service_register_uri(1, "as", 1, &request_recv_cb) )
                return false;

            if( -1 != coap_message_handler_stub.cb(1, coap, NULL) )
                return false;

            coap_transaction_t *tr = (coap_transaction_t *)malloc(sizeof(coap_transaction_t));
            memset(tr, 0, sizeof(coap_transaction_t));

            if( 2 != coap_message_handler_stub.cb(1, coap, tr) )
                return false;

            free(tr);
            tr = NULL;

            thread_conn_handler_stub.bool_value = false;
            free(coap);
            coap = NULL;
        }
    }

    if(thread_conn_handler_stub.get_passwd_cb){
        thread_conn_handler_stub.bool_value = true;
        if( 2 != thread_conn_handler_stub.get_passwd_cb(1, buf, 12, NULL, 0))
            return false;
        thread_conn_handler_stub.bool_value = false;
        if( -1 != thread_conn_handler_stub.get_passwd_cb(1, buf, 12, NULL, 0))
            return false;
    }

    if(thread_conn_handler_stub.sec_done_cb){
        uint8_t block[40];
        thread_conn_handler_stub.bool_value = true;

        coap_transaction_t *tr = (coap_transaction_t *)malloc(sizeof(coap_transaction_t));
        memset(tr, 0, sizeof(coap_transaction_t));
        nsdynmemlib_stub.returnCounter = 1;
        tr->data_ptr = ns_dyn_mem_alloc(1);
        tr->data_len = 1;
        coap_message_handler_stub.coap_tx_ptr = tr;

        thread_conn_handler_stub.sec_done_cb(1, buf, 12, block);

        free(tr);
        coap_message_handler_stub.coap_tx_ptr = NULL;

        thread_conn_handler_stub.bool_value = false;

    }

    coap_service_delete(1);
    free( thread_conn_handler_stub.handler_obj );
    thread_conn_handler_stub.handler_obj = NULL;

    return true;
}
