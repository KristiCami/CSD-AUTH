import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { ChatFeedComponent } from './chat-feed/chat-feed.component';

const routes: Routes = [
  {
    path: '',
    redirectTo: 'chat-feed',
    pathMatch: 'full'
  },
  {
    path: 'chat-feed',
    component: ChatFeedComponent
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {}
