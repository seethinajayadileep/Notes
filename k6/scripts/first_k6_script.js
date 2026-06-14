import http from 'k6/http'
import { sleep, check } from 'k6'

const BASE_URL = __ENV.BASE_URL || 'https://test.k6.io';

export const options = {

   stages:[
    { duration:'5s', target:5 },
    { duration:'3s', target:5 },
    { duration:'5s', target:0 },
   ],

    thresholds:{
        http_req_duration: ['p(95)<500']
    },

};

export default function () {
    const response = http.get(BASE_URL);

    check(response, {
        'status is 200':(r) => r.status === 200,
    });

    sleep(1)
}

