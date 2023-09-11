#include <rclcpp/rclcpp.hpp>
#include <px4_msgs/msg/sensor_combined.hpp>
#include <fstream>
#include <thread> 
#include <cstdlib>

class SensorCombinedListener : public rclcpp::Node
{
public:
    explicit SensorCombinedListener() : Node("sensor_combined_listener")
    {
        rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
        auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 5), qos_profile);

        // Open a text file for writing
        output_file.open("All_sensors_data.csv");

        subscription_ = this->create_subscription<px4_msgs::msg::SensorCombined>("/fmu/out/sensor_combined", qos,
            [this](const px4_msgs::msg::SensorCombined::UniquePtr msg) {
                // Print to console
                system("clear");
                std::cout << "ts: "          << msg->timestamp    << std::endl;
                std::cout << "gyro_rad[0]: " << msg->gyro_rad[0]  << std::endl;
                std::cout << "gyro_rad[1]: " << msg->gyro_rad[1]  << std::endl;
                std::cout << "gyro_rad[2]: " << msg->gyro_rad[2]  << std::endl;
                std::cout << "gyro_integral_dt: " << msg->gyro_integral_dt << std::endl;
                std::cout << "accelerometer_timestamp_relative: " << msg->accelerometer_timestamp_relative << std::endl;
                std::cout << "accelerometer_m_s2[0]: " << msg->accelerometer_m_s2[0] << std::endl;
                std::cout << "accelerometer_m_s2[1]: " << msg->accelerometer_m_s2[1] << std::endl;
                std::cout << "accelerometer_m_s2[2]: " << msg->accelerometer_m_s2[2] << std::endl;
                std::cout << "accelerometer_integral_dt: " << msg->accelerometer_integral_dt << std::endl;


                // Check if the file is empty
                output_file.seekp(0, std::ios::end);
                if (output_file.tellp() == 0) {
                    // The file is empty, so write the headers
                    output_file << "timestamp,gyro_rad[0],gyro_rad[1],gyro_rad[2],gyro_integral_dt,accelerometer_timestamp_relative,accelerometer_m_s2[0],accelerometer_m_s2[1],accelerometer_m_s2[2],accelerometer_integral_dt" << std::endl;
                }

                // Now, write the data
                output_file << msg->timestamp << "," << msg->gyro_rad[0] << "," << msg->gyro_rad[1] << "," << msg->gyro_rad[2] << "," << msg->gyro_integral_dt << "," << msg->accelerometer_timestamp_relative << "," << msg->accelerometer_m_s2[0] << "," << msg->accelerometer_m_s2[1] << "," << msg->accelerometer_m_s2[2] << "," << msg->accelerometer_integral_dt << std::endl;

                
                std::this_thread::sleep_for(std::chrono::seconds(1));
            });
    }

private:
    std::ofstream output_file;
    rclcpp::Subscription<px4_msgs::msg::SensorCombined>::SharedPtr subscription_;
};


int main(int argc, char *argv[])
{
	std::cout << "Starting sensor_combined listener node..." << std::endl;
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	rclcpp::init(argc, argv);
    std::cout << "RECEIVED SENSOR DATA" << std::endl;
    std::cout << "============================="   << std::endl;
	rclcpp::spin(std::make_shared<SensorCombinedListener>());

	rclcpp::shutdown();
	return 0;
}
