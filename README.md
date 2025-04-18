# 🏥 Welcome to the Hospital Management System Project!

Hello there! 👋 This project is a C-based system designed to help manage various aspects of a hospital, including patient records, doctor schedules, and reporting.

It was developed as part of coursework at the British Columbia Institute of Technology.

## ✨ Features

This system includes functionalities for:

*   **Patient Management:** Adding new patients, updating patient information, searching for patients, and managing patient discharge.
*   **Doctor Scheduling:** Managing doctor availability and schedules.
*   **Data Persistence:** Patient and schedule data are stored in `.dat` files (`patients.dat`, `schedule.dat`, etc.).
*   **Reporting:** Generating various reports, such as:
    *   Room Usage (`room_usage.txt`)
    *   Doctor Utilization (`doctor_utilization_report.txt`)
    *   Discharged Patient Summaries (`discharged_reports.txt`)
    *   Active Patient Reports (`patient_reports.txt`)

## 🧮 Building and Running

This project uses CMake. To build and run it:

1.  **Ensure CMake is installed.**
2.  **Create a build directory:** `mkdir build && cd build`
3.  **Run CMake:** `cmake ..`
4.  **Build the project:** `cmake --build .` (or use `make` if that's your generator)
5.  **Run the executable:** The executable (likely named `hospital` or similar based on `CMakeLists.txt`) will be in the build directory or a subdirectory like `cmake-build-debug`.

```bash
# Example commands
mkdir build
cd build
cmake ..
cmake --build .
./hospital # Or the correct executable name
```

## 📚 Acknowledgments

This project was created for the **Procedural Programming (COMP 2510)** course at the **British Columbia Institute of Technology (BCIT)**.

Special thanks to the instructor, **Ayesha Anzer**, for their guidance and support.

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Happy coding! 💻