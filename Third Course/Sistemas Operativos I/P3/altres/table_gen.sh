#!/bin/bash

# Define constants
ROWS=6
COLS=6
constant=1000

# Open file for writing
exec 3>"results.md"

# Write Markdown table header
echo "|   | 0 | 1 | 2 | 3 | 4 | 5 |" >&3
echo "|---|---|---|---|---|---|---|" >&3

# Fill the table and write it to Markdown file
for ((i = 0; i < ROWS; i++)); do
    row="| $i |"
    for ((j = 0; j < COLS; j++)); do
        # Execute the binary to calculate value for each cell
        value=$(./out_out pagos.csv $i $j $constant)

        # Append value to row
        row="$row $value |"
    done
    # Write row to file
    echo "$row" >&3
done

# Close file
exec 3>&-

echo "Markdown table created successfully."
