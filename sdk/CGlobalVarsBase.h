#pragma once

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/public/globalvars_base.h

class CGlobalVarsBase {
public:
	// absolute time (per frame still - Use Plat_FloatTime() for a high precision real time 
	// perf clock, but not that it doesn't obey host_timescale/host_framerate)
	float real_time; // 0

	// absolute frame counter
	int frame_count; // 4

	// non-paused frametime
	float absolute_frame_time; // 8
	float absolute_frame_start_time; // 12

	// current time 
	//
	// on the client, this (along with tickcount) takes a different meaning based on what
	// piece of code you're in:
	// 
	//   - while receiving network packets (like in PreDataUpdate/PostDataUpdate and proxies),
	//     this is set to the SERVER TICKCOUNT for that packet. There is no interval between
	//     the server ticks.
	//     [server_current_Tick * tick_interval]
	//
	//   - while rendering, this is the exact client clock 
	//     [client_current_tick * tick_interval + interpolation_amount]
	//
	//   - during prediction, this is based on the client's current tick:
	//     [client_current_tick * tick_interval]
	float current_time; // 16

	// time spent on last server or client frame (has nothing to do with think intervals)
	float frame_time; // 20

	// current maxplayers setting
	int max_clients; // 24

	// simulation ticks
	int tick_count;

	// simulation tick interval
	float interval_per_tick;

	// interpolation amount ( client-only ) based on fraction of next tick which has elapsed
	float interpolation_amount;
	int sim_ticks_this_frame;
	int network_protocol;

	// current saverestore data
	void* save_data;

	// set to true in client code.
	bool client;
	bool remove_client;

	// 100 (i.e., tickcount is rounded down to this base and then the "delta" from this base is networked
	int time_stamp_networking_base;

	// 32 (entindex() % nTimestampRandomizeWindow ) is subtracted from gpGlobals->tickcount to set the networking basis, prevents
	// all of the entities from forcing a new PackedEntity on the same tick (i.e., prevents them from getting lockstepped on this)
	int time_stamp_randomize_window;
};