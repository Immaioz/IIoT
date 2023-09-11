from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    sensor_combined_listener_node = Node(
        package='px4_ros',
        executable='sensor_combined_listener',
        output='screen',
        shell=True,
    )

    return LaunchDescription([
        sensor_combined_listener_node
    ])
