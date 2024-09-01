cmake_minimum_required(VERSION 3.28)
project(inpr_project_devc_supported C)

set(CMAKE_C_STANDARD 11)

add_executable(inpr_project_devc_supported main.c
        customer.c)
add_executable(customer customer.c)
add_executable(cashier cashier.c)
add_executable(poe poe_system.c)
