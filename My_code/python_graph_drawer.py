
import matplotlib.pyplot as pplt
from matplotlib import style
import pandas as csv

figure = pplt.figure()

graph_data = csv.read_csv("C:\\Users\\olegm\\OneDrive\\Документы\\new_graph.csv", delimiter= ";", names= ['problem size', 'GSM', 'KBM', 'DNC'])

pplt.plot(graph_data['problem size'], graph_data['GSM'], color= 'orange', label= 'Grade School Algo.')
pplt.plot(graph_data['problem size'], graph_data['KBM'], color= 'red', label= 'Karatsuba Algo.')
pplt.plot(graph_data['problem size'], graph_data['DNC'], color= 'blue', label= 'Divide & Conquer Algo. ')

style.use('seaborn-talk')
pplt.title("ADS Big Homework 1, Algorithms' complexity comparison")
pplt.ylabel('Time (in seconds)')
pplt.xlabel('Problem size (in num. of digits)')

pplt.legend()
pplt.show()
