# 🏥 Hospital Wait Time Processor

This Bash script processes patient data from a healthcare environment. It reads a dataset of patient records, calculates the **average wait time** for each hospital, **counts how many patients** each hospital has served, and **ranks hospitals** from the shortest to longest average wait time.

## What It Does

- Extracts hospital names and wait times from a structured dataset
- Calculates the average wait time per hospital
- Counts the number of patients per hospital
- Ranks hospitals in ascending order of average wait time
- Displays a formatted report with all results

## Why This Is Useful

- **Informed Decision-Making**: Hospital administrators can use this data to identify efficient hospitals and address bottlenecks.
- **Resource Allocation**: Knowing which hospitals are overburdened helps optimize staffing and funding.
- **Performance Benchmarking**: Enables comparison between hospitals to improve patient care and operational efficiency.

## Input Format

The script expects an input file where each line contains a patient record in the following format:

```
<PatientID> <Status> <Hospital Name> <Wait Time in Minutes>
```

Hospital names can have spaces, and wait time is expected to be the final value on the line.

### Example Input (`patient_data.txt`):
```
P1001 Admitted St. John's Hospital 30
P1002 Released City Medical Center 45
P1003 Admitted Riverside Hospital 20
P1004 Admitted City Medical Center 50
P1005 Released Green Valley Clinic 60
P1006 Admitted Green Valley Clinic 55
P1007 Admitted Riverside Hospital 35
P1008 Released St. John's Hospital 40
```

## Example Output

```
Hospital Name                  Avg Wait Time (min)   Number of Patients
------------------------------------------------------------
Lakeside Medical Center        15.00                1
St. John's Hospital            35.00                2
Riverside Hospital             27.50                2
City Medical Center            47.50                2
Green Valley Clinic            57.50                2
------------------------------------------------------------
```

## How to Run

1. Make the script executable:
```bash
chmod +x hospital_wait_analysis.sh
```

2. Run the script with your data file:
```bash
./hospital_wait_analysis.sh patient_data.txt
```
Replace `patient_data.txt` with the path to your actual input file.

## Notes

- Ensure each record ends with the wait time in minutes.
- The script ignores patient status and ID; it only uses the hospital name and wait time.
- Works with standard Bash; no additional dependencies are required.

## Use Cases

- Healthcare performance analysis
- Load balancing across hospitals
- Public health reporting and compliance
