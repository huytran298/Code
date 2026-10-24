import pandas as pd
import os

# Đổi lại đúng đường dẫn của bạn
folder_path = r'C:\Users\huyhuyne\Downloads\filebeday' 

data = {}

# 1. Xử lý file Phông (P) (Sửa lại tên file P cho đúng với thực tế của bạn)
file_p_path = os.path.join(folder_path, '120P_mix.txt') 
if os.path.exists(file_p_path):
    df_p = pd.read_csv(file_p_path, sep='\t', header=None)
    df_p = df_p.dropna(axis=1, how='all') # Bỏ cột rỗng bị dư do dấu tab
    data['Phông (P)'] = df_p.iloc[:, -1]
else:
    print(f"Không tìm thấy file: {file_p_path}")

# 2. Xử lý 16 file từ 120N01_mix.txt đến 120N16_mix.txt
for i in range(1, 17):
    file_name = f'120N{i:02d}_mix.txt' 
    file_path = os.path.join(folder_path, file_name)
    
    if os.path.exists(file_path):
        df_temp = pd.read_csv(file_path, sep='\t', header=None)
        df_temp = df_temp.dropna(axis=1, how='all') # Bỏ cột rỗng bị dư do dấu tab
        data[f'120N{i:02d}'] = df_temp.iloc[:, -1]
    else:
        print(f"Không tìm thấy file: {file_path}")

# 3. Gộp bảng và xuất Excel
df_final = pd.DataFrame(data)
output_excel = 'Ket_qua_tong_hop.xlsx'
df_final.to_excel(output_excel, index=False) 

print(f"Đã xuất dữ liệu thành công ra file: {output_excel}")