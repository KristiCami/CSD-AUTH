import { Component, OnInit, ViewChild, Renderer2 } from '@angular/core';
import { ChatService, Message } from '../chat-service.service';
import { VideoPlayer } from '@ionic-native/video-player/ngx';


@Component({
  selector: 'app-chat-feed',
  templateUrl: 'chat-feed.component.html',
  styleUrls: ['chat-feed.component.scss']
})
export class ChatFeedComponent implements OnInit {
  constructor(private chatService: ChatService, private renderer: Renderer2) {}

  messages: Message[] = [];

  ngOnInit() {
    this.getMessages();
  }

  getMessages() {
    this.chatService.getMessages().subscribe(messages => {
      this.messages = messages;
    });
  }

  playVideo(videoElement: HTMLVideoElement) {
    this.renderer.setAttribute(videoElement, 'autoplay', 'true');
    this.renderer.setAttribute(videoElement, 'muted', 'true');
    videoElement.play();
  }
  
}
