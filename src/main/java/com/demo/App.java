package com.demo;

import com.demo.rpc.service.Service;
import com.demo.rpc.service.SayHelloRequest;
import com.demo.rpc.service.SayHelloResponse;
import com.demo.rpc.shared.ServiceError;
import org.apache.thrift.TException;
import org.apache.thrift.TServiceClient;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.transport.TSocket;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class App {
    private Logger log = LoggerFactory.getLogger(getClass());

    private TSocket transport;
    private Service.Client client;

    public synchronized void initialize() {
        try {
            int port = 6565;            // thrift server port
            String host = "0.0.0.0";    // thrift server hostname
            int retryCount = 10;        // number of times to retry connection
            int waitTimeMs = 1000;      // interval between successive connection attempt

            log.info("Connecting with host = {}, port = {}", host, port);
            for (int attempt = 1; attempt <= retryCount; attempt++) {
                try {
                    transport = new TSocket(host, port);
                    transport.open();
                    break;
                } catch (TException ex) {
                    log.info("Connection attempt {} failed", attempt);
                    if (attempt == retryCount) {
                        throw ex;
                    }
                    Thread.sleep(waitTimeMs);
                }
            }

            // Create a thrift client using binary protocol
            log.info("Creating client...");
            TBinaryProtocol protocol = new TBinaryProtocol(transport);
            client = new Service.Client(protocol);
            log.info("Client initialized");
        } catch (InterruptedException | TException ex) {
            log.error("Failed to initialize client", ex);
        }
    }

    public void sendPing() throws TException {
        log.info("Sending ping");
        boolean result = client.ping();
        log.info("Received: {}", result);
    }

    public void sayHello(String name) throws TException {
        log.info("(sayHello) Request name: {}", name);
        try {
            SayHelloRequest request = new SayHelloRequest();
            request.name = name;
            SayHelloResponse response = client.sayHello(request);
            log.info("(sayHello) Response message: {}", response.message);
        } catch (ServiceError ex) {
            log.error("(sayHello) Error: {} ~ {}", ex.code, ex.message);
        }
    }

    public static void main(String[] args) throws TException {
        App app = new App();
        app.initialize();
        app.sendPing();
        app.sayHello("Dipu");
        app.sayHello("");
        app.sayHello("World");
    }
}
