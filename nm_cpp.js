var input = `von Braun believed in testing. I cannot
emphasize that term enough - test, test,
test. Test to the point it breaks.
- Ed Buckbee, NASA Public Affairs Officer, Chasing the Moon`;

(async()=>{
    self.port = chrome.runtime.connectNative('nm_cpp')

    port.onMessage.addListener((message)=>{
        if (chrome.runtime.lastError) {
            console.log(chrome.runtime.lastError.message)
        }
        console.log(message);
    }
    )

    port.onDisconnect.addListener(()=>{
        if (chrome.runtime.lastError) {
            console.log(chrome.runtime.lastError.message)
        }
        console.log('Disconnected')
    }
    )

    port.postMessage(input)
}
)();

chrome.runtime.sendNativeMessage('nm_cpp', new String(input))
.then((msg)=>console.log(msg, msg.length)).catch(console.error);
