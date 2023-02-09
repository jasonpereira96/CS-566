const N = 8;
for (let round=0; round<3; round++) {
    for (let id=0; id<N; id++) {
        printPartner(id, round);
    }
}
function printPartner(id, round) {
    let partnerDistance = 2 ** round;
    let mask = 2 ** round;
    let partnerId;
    if ((id & mask) === 0) {
        partnerId = id + partnerDistance;
    } else {
        partnerId = id - partnerDistance;
    }
    console.log(`My id: ${id} | partner id: ${partnerId}`);
}