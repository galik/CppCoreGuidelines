### <a name="Rper-access"></a>Per.19: Access memory predictably

##### Reason

Performance is very sensitive to cache performance and cache algorithms favor simple (usually linear) access to adjacent data.

##### Example

    int matrix[rows][cols];

    // bad
    for (int c = 0; c < cols; ++c)
        for (int r = 0; r < rows; ++r)
            sum += matrix[r][c];

    // good
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            sum += matrix[r][c];

