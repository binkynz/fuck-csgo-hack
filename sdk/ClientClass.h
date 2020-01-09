#pragma once

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/public/dt_recv.h
// https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/public/client_class.h

struct RecvProxyData;
struct RecvTable;
struct RecvProp;

using RecvVarProxy_t = void( __cdecl* )(const RecvProxyData*, void*, void*);
using CreateClientClass_t = void* (*)(int, int);
using CreateEvent_t = void* (*)();

struct DVariant {
	union {
		float float_type;
		long int_type;
		char* string_type;
		void* data_type;
		float vector_type[ 3 ];
		__int64 int_64_type;
	};
	int type;
};

struct RecvProxyData {
	const RecvProp* prop;
	DVariant value;
	int element;
	int object_id;
};

struct RecvTable {
	RecvProp* prop;
	int props;
	void* decoder;
	char* net_table_name;
	bool is_initialized;
	bool is_in_main_list;
};

struct RecvProp {
	char* var_name;
	int recv_type;
	int flags;
	int string_buffer_size;
	bool is_inside_array;
	const void* extra_data;
	RecvProp* array_prop;
	void* array_length_proxy;
	RecvVarProxy_t var_proxy;
	void* data_table_proxy;
	RecvTable* data_table;
	int offset;
	int element_stride;
	int elements;
	const char* parent_array_prop_name;
};

class ClientClass {
public:
	CreateClientClass_t client;
	CreateEvent_t event;
	char* network_name;
	RecvTable* table;
	ClientClass* next;
	int class_id;
};