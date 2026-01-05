
# pub-sub system
# topics: string keys
# publish(topic, message)
# subscribe(topic, callback)
# unsubscribe(topic, callback)

from collections import defaultdict
import threading

class PubSub:
    def __init__(self):
        self._subscribers = defaultdict(list)
        self._lock = threading.Lock()

    def subscribe(self, topic, callback):
        with self._lock:
            self._subscribers[topic].append(callback)

    def unsubscribe(self, topic, callback):
        with self._lock:
            if topic in self._subscribers:
                self._subscribers[topic] = [
                    cb for cb in self._subscribers[topic] if cb != callback
                ]

    def publish(self, topic, message):
        with self._lock:
            callbacks = list(self._subscribers.get(topic, []))
        # fire callbacks outside lock
        for callback in callbacks:
            callback(message)


def main():
    ps = PubSub()

    def handler1(msg):
        print(f"handler1 got: {msg}")

    def handler2(msg):
        print(f"handler2 got: {msg}")

    ps.subscribe("events", handler1)
    ps.subscribe("events", handler2)
    ps.subscribe("alerts", handler1)

    ps.publish("events", "login")
    ps.publish("alerts", "disk_full")

    ps.unsubscribe("events", handler2)
    ps.publish("events", "logout")


main()
