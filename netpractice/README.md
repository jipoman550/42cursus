*This project has been created as part of the 42 curriculum by sisung.*

## **Description**

NetPractice is a project focused on the fundamentals of computer networking. The goal is to solve 10 levels of simulated network configurations to make each network functional. Through this exercise, I learned how to configure TCP/IP addresses, understand subnet masks, and manage data routing through default gateways, routers, and switches.

## **Instructions**

### **How to Run**

1. Download and extract the project files.


2. Run the `run.sh` script in your terminal to launch the local web server and open the interface in your browser.


3. Alternatively, you can run `python3 -m http.server 49242` and navigate to `http://localhost:49242`.


4. Enter your login (`sisung`) in the interface to access your personal configuration.



### **Exporting and Submission**

* To save your progress, use the **[Get my config]** button to export a configuration file for each level.


* You must submit exactly **10 exported configuration files** (one per level).


* All 10 files must be placed at the **root of your Git repository**.



## **Resources**

### **Networking Concepts Studied**

This project covered several essential networking concepts:

* **TCP/IP Addressing**: Assigning and managing IP addresses within a network.
* **Subnet Masks**: Defining network boundaries and calculating available host ranges (e.g., /24, /30, /18).
* **Default Gateways**: Identifying the exit point for packets leaving a local network.
* **Routers and Switches**: Understanding how data is forwarded between different subnets or within the same local area network.
* **OSI Layers**: Specifically focusing on Layer 2 (Data Link) and Layer 3 (Network) interactions.

### **AI Usage Disclosure**

AI was utilized as a collaborative tutor during this project to strengthen my understanding of complex scenarios:

* **Troubleshooting**: AI helped analyze error logs such as "multiple interface match" (Level 4) and "private subnets not routed" (Level 9), explaining the underlying logic of subnet overlaps.
* **Mathematical Explanation**: AI assisted in calculating CIDR ranges and bitwise AND operations for non-standard masks like /18 or /26.
* **Logical Validation**: After solving levels, I used AI to verify why certain routing paths (Static Routes) were necessary for return traffic (Reverse Way).
* **README Generation**: AI assisted in formatting this documentation to ensure all 42 curriculum requirements were met.
