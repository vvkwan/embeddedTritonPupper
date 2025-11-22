import rclpy
from rclpy.node import Node

class SerialSender(Node):
    def __init__():

def main(args=None):
    rclpy.init(args=args)
    serialSender = SerialSender()
    rclpy.spin(serialSender)
    serialSender.destroy_node()
    rclpy.shutdown()
    

if __name__ == '__main__':
    main()
