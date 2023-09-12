#include <rclcpp/rclcpp.hpp>
#include <px4_msgs/msg/sensor_gps.hpp>
#include <fstream>
#include <cstdlib>

class VehicleGpsPositionListener : public rclcpp::Node
{
public:
	explicit VehicleGpsPositionListener() : Node("vehicle_global_position_listener")
	{
		rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
		auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 5), qos_profile);

		output_file.open("All_gps_data.csv");
		
		subscription_ = this->create_subscription<px4_msgs::msg::SensorGps>("/fmu/out/vehicle_gps_position", qos,
		[this](const px4_msgs::msg::SensorGps::UniquePtr msg) {
			system("clear");
			std::cout << "ts: "      << msg->timestamp    << std::endl;
			std::cout << "lat: " << msg->latitude_deg  << std::endl;
			std::cout << "lon: " << msg->longitude_deg << std::endl;
			std::cout << "alt: " << msg->altitude_msl_m  << std::endl;
			std::cout << "alt_ellipsoid: " << msg->altitude_ellipsoid_m << std::endl;
			std::cout << "s_variance_m_s: " << msg->s_variance_m_s << std::endl;
			std::cout << "c_variance_rad: " << msg->c_variance_rad << std::endl;
			std::cout << "eph: " << msg->eph << std::endl;
			std::cout << "epv: " << msg->epv << std::endl;
			std::cout << "hdop: " << msg->hdop << std::endl;
			std::cout << "vdop: " << msg->vdop << std::endl;
			std::cout << "noise_per_ms: " << msg->noise_per_ms << std::endl;
			std::cout << "vel_m_s: " << msg->vel_m_s << std::endl;
			std::cout << "vel_n_m_s: " << msg->vel_n_m_s << std::endl;
			std::cout << "vel_e_m_s: " << msg->vel_e_m_s << std::endl;
			std::cout << "vel_d_m_s: " << msg->vel_d_m_s << std::endl;
			std::cout << "cog_rad: " << msg->cog_rad << std::endl;
			std::cout << "vel_ned_valid: " << msg->vel_ned_valid << std::endl;
			std::cout << "timestamp_time_relative: " << msg->timestamp_time_relative << std::endl;
			std::cout << "time_utc_usec: " << msg->time_utc_usec << std::endl;
			std::cout << "satellites_used: " << msg->satellites_used << std::endl;
			std::cout << "heading: " << msg->heading << std::endl;
			std::cout << "heading_offset: " << msg->heading_offset << std::endl;


			output_file.seekp(0, std::ios::end);
			if (output_file.tellp() == 0) {
				// The file is empty, so write the headers
				output_file << "ts,lat,lon,alt,alt_ellipsoid,s_variance_m_s,c_variance_rad,eph,epv,hdop,vdop,noise_per_ms,vel_m_s,vel_n_m_s,vel_e_m_s,vel_d_m_s,cog_rad,vel_ned_valid,timestamp_time_relative,time_utc_usec,satellites_used,heading,heading_offset" << std::endl;
			}
			output_file << msg->timestamp << "," << msg->latitude_deg << "," << msg->longitude_deg << "," << msg->altitude_msl_m << "," << msg->altitude_ellipsoid_m << "," << msg->s_variance_m_s << "," << msg->c_variance_rad << "," << msg->eph << "," << msg->epv << "," << msg->hdop << "," << msg->vdop << "," << msg->noise_per_ms << "," << msg->vel_m_s << "," << msg->vel_n_m_s << "," << msg->vel_e_m_s << "," << msg->vel_d_m_s << "," << msg->cog_rad << "," << msg->vel_ned_valid << "," << msg->timestamp_time_relative << "," << msg->time_utc_usec << "," << msg->satellites_used << "," << msg->heading << "," << msg->heading_offset << std::endl;

		});
	}

private:
    std::ofstream output_file; // Declare an ofstream for writing to the file
	rclcpp::Subscription<px4_msgs::msg::SensorGps>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
	std::cout << "Starting vehicle_global_position listener node..." << std::endl;
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	rclcpp::init(argc, argv);
	std::cout << "RECEIVED VEHICLE GPS POSITION DATA"<< std::endl;
	std::cout << "=================================="<< std::endl;
	rclcpp::spin(std::make_shared<VehicleGpsPositionListener>());

	rclcpp::shutdown();
	return 0;
}
