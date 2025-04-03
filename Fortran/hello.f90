program quadratic_solver
    implicit none
    real :: a, b, c
    real :: discriminant, root1, root2

    ! Input coefficients
    print *, 'Enter coefficients a, b, and c:'
    read *, a, b, c

    ! Calculate the discriminant
    discriminant = b**2 - 4.0 * a * c

    if (discriminant > 0.0) then
        ! Two real and distinct roots
        root1 = (-b + sqrt(discriminant)) / (2.0 * a)
        root2 = (-b - sqrt(discriminant)) / (2.0 * a)
        print *, 'Roots are real and different.'
        print *, 'Root 1 = ', root1
        print *, 'Root 2 = ', root2
    else if (discriminant == 0.0) then
        ! One real root
        root1 = -b / (2.0 * a)
        print *, 'Roots are real and the same.'
        print *, 'Root = ', root1
    else
        ! Complex roots
        print *, 'Roots are complex and different.'
        print *, 'Root 1 = ', -b / (2.0 * a), ' + i', sqrt(-discriminant) / (2.0 * a)