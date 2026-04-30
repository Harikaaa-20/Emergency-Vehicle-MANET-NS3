import matplotlib.pyplot as plt

labels = ['Emergency', 'Normal']

packets_sent = [8544, 3417]
packets_received = [8430, 3382]
packet_loss = [114, 35]
pdr = [98.66, 98.97]

# Graph 1: Packets Sent
plt.figure()
plt.bar(labels, packets_sent)
plt.title("Packets Sent Comparison")
plt.xlabel("Traffic Type")
plt.ylabel("Packets Sent")
plt.savefig("packets_sent.png")

# Graph 2: Packets Received
plt.figure()
plt.bar(labels, packets_received)
plt.title("Packets Received Comparison")
plt.xlabel("Traffic Type")
plt.ylabel("Packets Received")
plt.savefig("packets_received.png")

# Graph 3: Packet Loss
plt.figure()
plt.bar(labels, packet_loss)
plt.title("Packet Loss Comparison")
plt.xlabel("Traffic Type")
plt.ylabel("Packets Lost")
plt.savefig("packet_loss.png")

# Graph 4: Packet Delivery Ratio
plt.figure()
plt.bar(labels, pdr)
plt.title("Packet Delivery Ratio Comparison")
plt.xlabel("Traffic Type")
plt.ylabel("Percentage (%)")
plt.savefig("pdr.png")

print("Graphs generated successfully!")
