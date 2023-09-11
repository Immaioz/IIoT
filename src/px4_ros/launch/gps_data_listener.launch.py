from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    gps_data_listener_node = Node(
        package='px4_ros',
        executable='vehicle_gps_position_listener',
        output='screen',
        shell=True,
    )

    return LaunchDescription([
        gps_data_listener_node
    ])
