#!/bin/bash

# This Bash script processes patient data from a healthcare environment.
# The program will read a dataset of patient records, calculate the average wait time 
# for each hospital, and rank the hospitals based on their average wait time from least to most.
# Additionally, it will also calculate the number of patients each hospital has served.

# Define the dataset file (passed by the user)
echo "Enter the dataset file name (e.g., patient_data.txt):"
read filename

# Check if the file exists
if [[ ! -f "$filename" ]]; then
  echo "File not found!"
  exit 1
fi

# Declare associative arrays to store total wait time and patient counts for each hospital
declare -A total_wait_time
declare -A patient_count

# Process the dataset line by line
while read -r patient_id status hospital wait_time; do
  # If the line has valid data
  if [[ ! -z "$hospital" && ! -z "$wait_time" && "$wait_time" =~ ^[0-9]+$ ]]; then
    # Accumulate total wait time for the hospital
    total_wait_time["$hospital"]=$((total_wait_time["$hospital"] + wait_time))
    
    # Increment the patient count for the hospital
    patient_count["$hospital"]=$((patient_count["$hospital"] + 1))
  fi
done < "$filename"

# Prepare an array to hold hospital names for sorting
hospitals=("${!total_wait_time[@]}")

# Sort hospitals by average wait time in ascending order (least to most)
for hospital in "${hospitals[@]}"; do
  avg_wait_time=$(echo "${total_wait_time[$hospital]} / ${patient_count[$hospital]}" | bc -l)
  avg_wait_time=$(printf "%.2f" "$avg_wait_time")
  
  # Store the hospital and its average wait time
  sorted_data+=("$avg_wait_time $hospital ${patient_count[$hospital]}")
done

# Sort the data by average wait time (ascending)
sorted_data=$(echo "${sorted_data[@]}" | tr ' ' '\n' | sort -n | tr '\n' ' ')

# Display the results
echo "Hospital Wait Time Rankings (Least to Most) - in minutes:"
echo "------------------------------------------------------------"
echo "Hospital Name                  Avg Wait Time (min)   Number of Patients"
echo "------------------------------------------------------------"
for entry in $sorted_data; do
  # Extract hospital name, average wait time, and patient count
  avg_wait_time=$(echo $entry | cut -d' ' -f1)
  hospital_name=$(echo $entry | cut -d' ' -f2- | cut -d' ' -f1-)
  patient_count=$(echo $entry | cut -d' ' -f3)

  # Display the information for each hospital
  printf "%-30s %-20s %-10s\n" "$hospital_name" "$avg_wait_time" "$patient_count"
done
echo "------------------------------------------------------------"

# Output explanation:
# 1. The program calculates the **average wait time** for each hospital by dividing the total wait time by the number of patients served.
# 2. It **ranks the hospitals** from least to most average wait time, making it easy to identify high-performing hospitals.
# 3. The program also displays the **number of patients** served by each hospital, which can help with resource allocation.

# Why this is useful:
# - **Improved Decision Making**: Helps hospital administrators make data-driven decisions about resource allocation, staffing, and operational improvements.
# - **Resource Allocation**: Identifying which hospitals have the highest patient load or longest wait times allows for better resource management.
# - **Operational Insights**: Helps benchmark hospitals against each other, leading to improved patient care and performance.

# Example of input data format:
# P1001 Admitted St. John's Hospital 30
# P1002 Released City Medical Center 45
# P1003 Admitted Riverside Hospital 20
# ...

# Example output format:
# Hospital Name                  Avg Wait Time (min)   Number of Patients
# ------------------------------------------------------------
# Lakeside Medical Center        15.00                1
# St. John's Hospital            35.00                2
# Riverside Hospital             27.50                2
# City Medical Center            47.50                2
# Green Valley Clinic            57.50                2
# ------------------------------------------------------------
