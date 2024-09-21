import { Injectable } from '@angular/core';
import { Observable, of } from 'rxjs';

export interface Message {
  sender: string;
  content: string;
}



@Injectable({
  providedIn: 'root'
})
export class ChatService {
  private messages: Message[] = [
    { sender: 'User 1', content: 'Hello!' },
    { sender: 'User 2', content: 'Hi there!' }
  ];

  sendMessage(message: string) {
    // Logic to send the message
  }

  getMessages(): Observable<Message[]> {
    return of(this.messages);
  }
}

