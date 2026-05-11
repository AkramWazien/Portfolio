import pandas as pd

df = pd.read_csv("C:\\Users\\User\\arduino\\Coding\\Python\\Pandas\\data.csv", index_col="Name")

df = df.drop(columns=["Generation"])
df["Type2"] = df["Type2"].replace({" ": "None"})
df.index = df.index.str.upper()
df = df.drop_duplicates()
print(df)