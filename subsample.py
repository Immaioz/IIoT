import csv

# Input and output file paths
input_file_path = 'All_gps_data.csv'  # Replace with the path to your CSV file
output_file_path = 'output.txt'  # Replace with the path for the output file


with open(input_file_path, 'r', newline='') as csvfile, open(output_file_path, 'w') as outfile:
    reader = csv.reader(csvfile)
    writer = csv.writer(outfile)

    header = next(reader)
    writer.writerow(header)  # Write the header row to the output file

    count = 0
    for row in reader:
        count += 1
        if count % 50 == 0:
            writer.writerow(row)