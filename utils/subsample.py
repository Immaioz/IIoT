import csv
import argparse

def filter_csv(input_file_path, output_file_path, interval):
    with open(input_file_path, 'r', newline='') as csvfile, open(output_file_path, 'w') as outfile:
        reader = csv.reader(csvfile)
        writer = csv.writer(outfile)

        header = next(reader)
        writer.writerow(header)  # Write the header row to the output file

        count = 0
        for row in reader:
            count += 1
            if count % interval == 0:
                writer.writerow(row)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Filter rows from a CSV file based on an interval.')
    parser.add_argument('-i', help='Input CSV file path')
    parser.add_argument('-o', help='Output file path')
    parser.add_argument('-n', type=int, default=50, help='Interval for filtering (default is 50)')

    args = parser.parse_args()
    filter_csv(args.i, args.o, args.n)
