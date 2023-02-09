int N, P;
int m; // number of rows (power of 2)
int n; // number of cols (power of 2)

int parallel_sum(int elements[]) {
    int result = sum(elements); // Initialize result
    int id = myid(); // get the current processors id
    int row = floor(id / m); // get the current processors row id
    int col = id % n; // get the current processors col id
    
    int round = 0;
    int mask = pow(2, round);

    // Communication along the rows
    int N_ROUNDS = log(n);

    for (int round=0; round < N_ROUNDS; round++) {
        int partnerDistance = pow(2, round);
        int mask = pow(2, round);
        // partnerId is the id of the processor this processor will be communicating with in this round
        int partnerId;
        if ((id & mask) == 0) {
            partnerId = row + partnerDistance;
        } else {
            partnerId = row - partnerDistance;
        }
        // send the current result to the partner
        send(partnerId, result);
        // recieve from the partner
        int received = receive(partnerId, result);
        // add the received sum to the current sum
        result = result + received;
    }

    // Communication along the cols
    N_ROUNDS = log(m);

    for (int round=0; round < N_ROUNDS; round++) {
        int partnerDistance = pow(2, round);
        int mask = pow(2, round);
        int partnerId;
        if ((id & mask) == 0) {
            partnerId = col + partnerDistance;
        } else {
            partnerId = col - partnerDistance;
        }
        send(partnerId, result);
        int received = receive(partnerId, result);
        result = result + received;
    }
    // The final sum is accumulated in this variable
    print(result);
    return 0;
}