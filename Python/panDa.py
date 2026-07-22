import pandas as pd
import numpy as np

pd.set_option("display.max_columns", None)

pd.set_option("display.max_colwidth", None)

df = pd.read_csv('titanic.csv')
print(df.tail(20))