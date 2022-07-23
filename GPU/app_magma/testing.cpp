#include <app_magma/testing.hpp>

using namespace std;

namespace Testing
{
    // Constructor
    YsunYpyjac::YsunYpyjac(double *_ySunHost, double *_ySunGPU, double *_yPyjacHost, double *_yPyjacGPU) \
        : ySunHost{_ySunHost}, ySunGPU{_ySunGPU}, yPyjacHost{_yPyjacHost}, yPyjacGPU{_yPyjacGPU} {
        
        string headerLogger {"Testing"};

        infoLogger = make_unique<Utils::Logger>(headerLogger, "INFO");
        errorLogger = make_unique<Utils::Logger>(headerLogger, "ERROR");
    }

    void YsunYpyjac::set_simulation_size(int num_systems, int num_species, int _padded) {
        systems = num_systems;
        nsp = num_species;

        // Padded is the number of systems used by pyjac
        padded = _padded;

        total_bytes_sun = systems * nsp * sizeof(double);
        total_bytes_py = padded * nsp * sizeof(double);
    }


    void YsunYpyjac::ysun_vs_ypyjac() {

        /* Move data from GPU to CPU */
        
        cuda_err = cudaMemcpy(ySunHost, ySunGPU, total_bytes_sun, cudaMemcpyDeviceToHost);
        if (cuda_err != cudaSuccess)
        {
            char error_message [100];
            sprintf(error_message, "cudaMemcpy ySunHost <- ySunGPU returned error code %d, line(%d)\n", cuda_err, __LINE__);
            errorLogger->print_message(__func__, __LINE__, error_message);
        }

        errorLogger->print_message(__func__, __LINE__, "Here is the error! We are trying to access more data than available");
        cuda_err = cudaMemcpy(yPyjacHost, yPyjacGPU, total_bytes_py, cudaMemcpyDeviceToHost);
        if (cuda_err != cudaSuccess)
        {
            char error_message [100];
            sprintf(error_message, "cudaMemcpy yPyjacHost <- yPyjacGPU returned error code %d, line(%d)\n", cuda_err, __LINE__);
            errorLogger->print_message(__func__, __LINE__, error_message);
        }


        double error{0.0f};

        /* Sum each array and compare the size */

        // Sundials
        // ySun = {T0, Y00, Y01, ... Y0(NSP-1), T1, Y10, Y11, ... Y1(NSP-1), ...}
        double total_sun{0.0f};
        for (int i = 0; i < systems * nsp; i++) {
            total_sun += ySunHost[i];
        }

        infoLogger->print_message(__func__, __LINE__, "Total sum of Sundials array = " + to_string(total_sun));


        // Pyjac
        // yPy  = {T0,  T1,  T2, ...  T(nSystems), Y00, Y10, Y20, ..., Y(nSystems)0, Y01, Y11, Y21, ..., Y(nSystems)1, ...}
        double total_pyjac{0.0f};
        for (int i = 0; i < nsp; i++) {
            for (int j = 0; j < systems; j++) {
                total_pyjac += yPyjacHost[i * padded + j];
            }
        }

        infoLogger->print_message(__func__, __LINE__,  "Total sum of Pyjac array = " + to_string(total_pyjac));

        error = abs(total_sun - total_pyjac);

        string message = "Difference between ySunHost and yPyjacHost = " + to_string(error);
        infoLogger->print_message(__func__, __LINE__, message);
    }
} // namespace Testing

