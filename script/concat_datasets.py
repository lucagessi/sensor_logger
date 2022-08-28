import numpy as np
import pandas as pd
from datetime import datetime
import os

folder = "./for_training/"

df_cols = ['class', 'x','y','z']

main_df = pd.DataFrame(data=None, columns=df_cols)

for f in os.listdir(folder):
    if f.endswith(".json"):
        print(f)
        df = pd.read_json( folder + f )
        main_df = pd.concat([main_df, df], ignore_index=True )

print("Data concatenated")
now = datetime.now()

main_df.to_json("dataset_"+now.strftime("%d-%m-%Y %H:%M.json"))



