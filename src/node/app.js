'use strict';

const http = require('http');
const https = require('https');
const crypto = require('crypto');

const HOST = 'api.line.me';
const REPLY_PATH = '/v2/bot/message/reply';//リプライ用
const CH_SECRET = 'xxxxxxxx'; //Channel Secretを指定
const CH_ACCESS_TOKEN = 'xxxxxx'; //Channel Access Tokenを指定
const SIGNATURE = crypto.createHmac('sha256', CH_SECRET);
const PORT = process.env.PORT || 3000;

//milkcocoa
var MilkCocoa = require('milkcocoa');
var milkcocoa = MilkCocoa.connectWithApiKey('...your-app-id.mlkcca.com...', '...API_Key...', '...API_Secret...');
var ds = milkcocoa.dataStore('...DataStore...');

/**
 * httpリクエスト部分
 */
const client = (replyToken, SendMessageObject) => {
    let postDataStr = JSON.stringify({ replyToken: replyToken, messages: SendMessageObject });
    let options = {
        host: HOST,
        port: 443,
        path: REPLY_PATH,
        method: 'POST',
        headers: {
            'Content-Type': 'application/json; charset=UTF-8',
            'X-Line-Signature': SIGNATURE,
            'Authorization': `Bearer ${CH_ACCESS_TOKEN}`,
            'Content-Length': Buffer.byteLength(postDataStr)
        }
    };

    return new Promise((resolve, reject) => {
        let req = https.request(options, (res) => {
                    let body = '';
                    res.setEncoding('utf8');
                    res.on('data', (chunk) => {
                        body += chunk;
                    });
                    res.on('end', () => {
                        resolve(body);
                    });
        });

        req.on('error', (e) => {
            reject(e);
        });
        req.write(postDataStr);
        req.end();
    });
};

http.createServer((req, res) => {
    if(req.url !== '/' || req.method !== 'POST'){
        res.writeHead(200, {'Content-Type': 'text/plain;charset=utf-8'});
        res.end('こんにちは世界');
    }

    let body = '';
    req.on('data', (chunk) => {
        body += chunk;
    });
    req.on('end', () => {
        if(body === ''){
          console.log('bodyが空です。');
          return;
        }

        let WebhookEventObject = JSON.parse(body).events[0];
        console.log(WebhookEventObject);
        //メッセージが送られて来た場合
        if(WebhookEventObject.type === 'message'){
            let SendMessageObject;
            if(WebhookEventObject.message.type === 'text' && WebhookEventObject.message.text === 'おなかすいた'){
                ds.push({ t : 1 });
                SendMessageObject = [{
                    type: 'text',
                    text: 'ぼくのかおをお食べえ'
                }];
            }
            client(WebhookEventObject.replyToken, SendMessageObject)
            .then((body)=>{
                console.log(body);
            },(e)=>{console.log(e)});
        }

        res.writeHead(200, {'Content-Type': 'text/plain'});
        res.end('su');
    });

}).listen(PORT);

console.log(`Server running at ${PORT}`);
