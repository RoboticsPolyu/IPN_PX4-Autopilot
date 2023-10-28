#pragma once

#include "mixer_module/mixer_module.hpp"

#include <board_config.h>
#include <drivers/drv_pwm_output.h>
#include <lib/mixer/MixerGroup.hpp>
#include <lib/perf/perf_counter.h>
#include <px4_platform_common/module_params.h>
#include <px4_platform_common/px4_work_queue/ScheduledWorkItem.hpp>
#include <uORB/Publication.hpp>
#include <uORB/PublicationMulti.hpp>
#include <uORB/Subscription.hpp>
#include <uORB/SubscriptionCallback.hpp>
#include <uORB/topics/actuator_armed.h>
#include <uORB/topics/actuator_outputs.h>



class MotorSysTest
{
public:
	MotorSysTest(OutputModuleInterface &interface);
	~MotorSysTest();

	void setAndPublishActuatorOutputs(unsigned num_outputs, actuator_outputs_s &actuator_outputs);

	void Run();

private:

	// Motor pwm publisher.
	uORB::PublicationMulti<actuator_outputs_s> _outputs_pub{ORB_ID(actuator_outputs)};

	OutputModuleInterface &_interface;

	// perf_counter_t _control_latency_perf;
};
