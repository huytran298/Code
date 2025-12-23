import re

def extract_n_counts(input_filepath, output_filepath):
    data_started = False
    data_line_pattern_source = re.compile(r"^\s*\\s+(\d+)\s+[\d.eE+-]+\s+(\d+)\s+.*")
    data_line_pattern_no_source = re.compile(r"^\s*(\d+)\s+[\d.eE+-]+\s+(\d+)\s+.*")
    separator_line = "#--------------------------------------------------"

    try:
        with open(input_filepath, 'r', encoding='utf-8') as infile, \
             open(output_filepath, 'w', encoding='utf-8') as outfile:

            for line in infile:
                stripped_line = line.strip()

                if stripped_line == separator_line:
                    data_started = True

                    continue

                if data_started and stripped_line:
                    match_source = data_line_pattern_source.match(line)
                    match_no_source = data_line_pattern_no_source.match(stripped_line)

                    if match_source:
                        n_val = match_source.group(1)
                        counts_val = match_source.group(2)
                        outfile.write(f"{counts_val}\n")
                    elif match_no_source:
                         parts = stripped_line.split()
                         if len(parts) >= 3 and parts[0].isdigit() and parts[2].isdigit():
                             n_val = parts[0]
                             counts_val = parts[2]
                             outfile.write(f"{counts_val}\n")

    except FileNotFoundError:
        print(f"Lỗi: Không tìm thấy file '{input_filepath}'")
    except Exception as e:
        print(f"Đã xảy ra lỗi: {e}")

# Gọi hàm để xử lý file
input_file = '/Users/huytranquoc/Documents/Code/input.txt'
output_file = '/Users/huytranquoc/Documents/Code/output.txt'
extract_n_counts(input_file, output_file)

print(f"Đã xử lý xong. Dữ liệu được ghi vào file '{output_file}'")