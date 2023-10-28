#include "mc_mpc_control.hpp"
#include "px4_platform_common/log.h"

#include <drivers/drv_pwm_output.h>
#include <sys/ioctl.h>



MotorSysTest::MotorSysTest(OutputModuleInterface &interface)
	:_interface(interface)
{
	_outputs_pub.advertise();
}

MotorSysTest::~MotorSysTest()
{
	_outputs_pub.unadvertise();
}


void MotorSysTest::setAndPublishActuatorOutputs(unsigned num_outputs, actuator_outputs_s &actuator_outputs)
{
	actuator_outputs.noutputs = num_outputs;

	// for (size_t i = 0; i < num_outputs; ++i) {
	// 	actuator_outputs.output[i] = _current_output_value[i];
	// }

	actuator_outputs.timestamp = hrt_absolute_time();

	// hrt_abstime timestamp_sample;
	// _functions[0]->getLatestSampleTimestamp(timestamp_sample); // hrt_absolute_time();
	// actuator_outputs.timestamp = timestamp_sample;

	_outputs_pub.publish(actuator_outputs);
}

void MotorSysTest::Run()
{
	bool stop_motors = false;
	uint16_t* _current_output_value = 0;
	unsigned _max_num_outputs = 1;
	unsigned has_updates = true;

	/* now return the outputs to the driver */
	if (_interface.updateOutputs(stop_motors, _current_output_value, _max_num_outputs, has_updates)) {
		actuator_outputs_s actuator_outputs{};
		setAndPublishActuatorOutputs(_max_num_outputs, actuator_outputs);

	}

}


extern "C" __EXPORT int mc_mpc_control_main(int argc, char *argv[])
{
	// MotorSysTest motor_sys_test;
	// motor_sys_test.Run();
	const char *dev = PWM_OUTPUT0_DEVICE_PATH;
	int fd = px4_open(dev, 0);//fd打开的是FMU通道
	if (fd < 0)
	{
		errx(1, "open fail");
	}

	int servo_count = 0;

	if(px4_ioctl(fd, PWM_SERVO_GET_COUNT, (unsigned long)&servo_count) != 0)
	{
		err(1, "Unable to get servo count\n");
	}

	int i = 1;
	uint PWM_VALUE = 1000;

	int ret = px4_ioctl(fd, PWM_SERVO_GET(i), PWM_VALUE);

	if (ret != OK)
	{
		PX4_ERR("PWM_SERVO_SET(%d)", i);
	}

	return 0;
}
