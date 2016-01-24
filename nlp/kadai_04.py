import os
import sys

def cosine(d,q):
    d_q=[d[i] * q[i] for i in range(len(d))]
    d_2=[d[i] * d[i] for i in range(len(d))]
    q_2=[q[i] * q[i] for i in range(len(q))]
    cos_d_q=(sum(d_q)/(sum(d_2)*sum(q_2))**.5)
    return cos_d_q

d1=[1,0,0,0,0,1,0,1]
d2=[0,1,1,1,0,1,0,1]
d3=[0,1,0,0,1,1,1,0]
d4=[0,1,0,0,0,1,2,0]
d5=[1,0,0,0,0,0,1,0]
d6=[0,1,0,0,1,0,0,0]

q1=[0,0,0,0,0,1,1,0]
q2=[1,0,0,0,0,0,0,1]

print("d1 to q1 : %.3f" % cosine(d1,q1))
print("d2 to q1 : %.3f" % cosine(d2,q1))
print("d3 to q1 : %.3f" % cosine(d3,q1))
print("d4 to q1 : %.3f" % cosine(d4,q1))
print("d5 to q1 : %.3f" % cosine(d5,q1))
print("d6 to q1 : %.3f" % cosine(d6,q1))

print("")

print("d1 to q2 : %.3f" % cosine(d1,q2))
print("d2 to q2 : %.3f" % cosine(d2,q2))
print("d3 to q2 : %.3f" % cosine(d3,q2))
print("d4 to q2 : %.3f" % cosine(d4,q2))
print("d5 to q2 : %.3f" % cosine(d5,q2))
print("d6 to q2 : %.3f" % cosine(d6,q2))