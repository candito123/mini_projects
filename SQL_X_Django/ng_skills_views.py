from django.shortcuts import render
from django.http import Http404

from .models import Skill
from projects.models import Project, Category

def skills(request, skill_id=1):
    try:
        skill = Skill.objects.get(id=skill_id)
    except Skill.DoesNotExist:
        raise Http404('skill not found')

    category_that_has_skill = Category.objects.filter(skill__isnull=False).distinct()
    projects_under_current_skill = Skill.objects.get(id=skill_id).project_set.all()

    return render(request, 'skills.html', {
        'category_that_has_skill': category_that_has_skill,
        'skill':skill,
        'projects_under_current_skill':projects_under_current_skill,
    })

def skills_whole(request):
    skill_set = Skill.objects.all()

    return render(request, 'skills_whole.html', {
        'skill_set':skill_set,
    })
