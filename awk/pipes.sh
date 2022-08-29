
# Sort sales by name
cat sales.txt | sort | less

# Sort sales by amount
cat sales.txt | sort -k 2 -nr | less

# Top 5
cat sales.txt | sort -k 2 -nr | head -n 5

# Smallest 5
cat sales.txt | sort -k 2 -nr | tail -n 5

# Combined sales with awk
cat sales.txt | awk '{arr[$1]+=$2} END {for (i in arr) {print i, arr[i]}}' | sort -k 2 -nr

# Transactions above 2500
cat sales.txt | awk '$2>2500 {print $1,$2}' | sort -k 2 -nr